#include "ModLoaderSubsystem.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "IPlatformFilePak.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/ARFilter.h"       // <--- ADDED
#include "AssetRegistry/AssetData.h"      // <--- ADDED
#include "Engine/Blueprint.h"             // <--- ADDED
#include "Engine/ObjectLibrary.h"

DEFINE_LOG_CATEGORY(LogModLoader);

void UModLoaderSubsystem::LoadMods()
{
	UE_LOG(LogModLoader, Log, TEXT("Starting Mod Load Process..."));

	// 1. Define the directory: Project/CarImports
	FString ModDirectory = FPaths::Combine(FPaths::ProjectDir(), TEXT("CarImports"));
	
	// 2. Scan for .pak files
	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (!PlatformFile.DirectoryExists(*ModDirectory))
	{
		UE_LOG(LogModLoader, Warning, TEXT("Mod Directory not found at: %s"), *ModDirectory);
		return;
	}

	TArray<FString> PakFiles;
	PlatformFile.FindFiles(PakFiles, *ModDirectory, TEXT("pak"));

	// 3. Mount each Pak
	for (const FString& File : PakFiles)
	{
		MountPakFile(File);
	}

	// 4. Force the Asset Registry to update synchronously
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FString> ScanPaths;
	ScanPaths.Add(TEXT("/Game/Mods")); // Ensure this matches your Pak mount point
	AssetRegistryModule.Get().ScanPathsSynchronous(ScanPaths, true);
	
	UE_LOG(LogModLoader, Log, TEXT("Mod Loading Complete."));
}

void UModLoaderSubsystem::MountPakFile(const FString& PakPath)
{
	FPakPlatformFile* PakPlatformFile = new FPakPlatformFile();
	IPlatformFile& InnerPlatformFile = FPlatformFileManager::Get().GetPlatformFile();
	
	if (!PakPlatformFile->Initialize(&InnerPlatformFile, TEXT("")))
	{
		UE_LOG(LogModLoader, Error, TEXT("Failed to initialize PakPlatformFile."));
		return;
	}

	// Mount logic
	if (PakPlatformFile->Mount(*PakPath, 0, NULL))
	{
		UE_LOG(LogModLoader, Log, TEXT("Successfully Mounted: %s"), *PakPath);
	}
	else
	{
		UE_LOG(LogModLoader, Error, TEXT("Failed to Mount: %s"), *PakPath);
	}
}

TArray<UClass*> UModLoaderSubsystem::GetLoadedVehicleClasses()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetDataList;
	
	FARFilter Filter;
	// Use ClassPathNames for UE 5.1+ compatibility
	Filter.ClassPaths.Add(UBlueprint::StaticClass()->GetClassPathName());
	Filter.PackagePaths.Add(FName("/Game/Mods")); 
	Filter.bRecursivePaths = true;
	
	AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

	LoadedVehicleClasses.Empty();

	for (const FAssetData& Asset : AssetDataList)
	{
		if (Asset.AssetName.ToString().StartsWith("BP_Car_"))
		{
			// FIXED: ObjectPath is deprecated. Use GetObjectPathString() + "_C" for the generated class
			FString ClassPath = Asset.GetObjectPathString() + "_C";
			
			UClass* LoadedClass = LoadObject<UClass>(NULL, *ClassPath);
			
			if (LoadedClass)
			{
				LoadedVehicleClasses.Add(LoadedClass);
				UE_LOG(LogModLoader, Log, TEXT("Found Vehicle: %s"), *Asset.AssetName.ToString());
			}
		}
	}

	return LoadedVehicleClasses;
}