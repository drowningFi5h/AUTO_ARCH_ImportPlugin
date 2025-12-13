#include "ModLoaderSubsystem.h"
#include "Misc/Paths.h"
#include "HAL/PlatformFilemanager.h"
#include "GenericPlatform/GenericPlatformFile.h"
#include "IPlatformFilePak.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "AssetRegistry/ARFilter.h"
#include "AssetRegistry/AssetData.h"
#include "Engine/Blueprint.h"
#include "Engine/ObjectLibrary.h"
#include "GameFramework/Actor.h" 

DEFINE_LOG_CATEGORY(LogModLoader);

void UModLoaderSubsystem::LoadMods()
{
	UE_LOG(LogModLoader, Warning, TEXT("--- STARTING MOD LOAD PROCESS ---"));

    IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();
    TArray<FString> PakFiles;

    // DEFINE SEARCH PATHS (Check both Project Dir and Exe Dir)
    TArray<FString> SearchPaths;
    SearchPaths.Add(FPaths::Combine(FPaths::ProjectDir(), TEXT("CAR_IMPORTS"))); // Standard
    SearchPaths.Add(FPaths::Combine(FPaths::LaunchDir(), TEXT("CAR_IMPORTS")));  // Next to EXE

    FString FoundDir = "";

    // FIND VALID DIRECTORY
    for (const FString& Dir : SearchPaths)
    {
        if (PlatformFile.DirectoryExists(*Dir))
        {
            FoundDir = Dir;
            UE_LOG(LogModLoader, Warning, TEXT("Found Mod Directory at: %s"), *FoundDir);
            break;
        }
    }

    if (FoundDir.IsEmpty())
    {
        UE_LOG(LogModLoader, Error, TEXT("CRITICAL: Could not find CAR_IMPORTS folder. Checked ProjectDir and LaunchDir."));
        return;
    }
	// SCAN FOR .PAK FILES
	PlatformFile.FindFiles(PakFiles, *FoundDir, TEXT("pak"));
    UE_LOG(LogModLoader, Warning, TEXT("Found %d .pak files."), PakFiles.Num());

	for (const FString& File : PakFiles)
	{
		MountPakFile(File);
	}

    // SCAN ASSET REGISTRY
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FString> ScanPaths;
	ScanPaths.Add(TEXT("/Game/CarImports")); 
	AssetRegistryModule.Get().ScanPathsSynchronous(ScanPaths, true);
	
	UE_LOG(LogModLoader, Warning, TEXT("Mod Loading Complete. Registry Scanned."));
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

	if (PakPlatformFile->Mount(*PakPath, 0, NULL))
	{
		UE_LOG(LogModLoader, Warning, TEXT("Mounted PAK: %s"), *PakPath);
	}
	else
	{
		UE_LOG(LogModLoader, Error, TEXT("Failed to Mount: %s"), *PakPath);
	}
}

TArray<TSubclassOf<AActor>> UModLoaderSubsystem::GetLoadedVehicleClasses()
{
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	TArray<FAssetData> AssetDataList;
	
	FARFilter Filter;
	Filter.ClassPaths.Add(UBlueprint::StaticClass()->GetClassPathName());
	Filter.PackagePaths.Add(FName("/Game/CarImports")); 
	Filter.bRecursivePaths = true;
	
	AssetRegistryModule.Get().GetAssets(Filter, AssetDataList);

	LoadedVehicleClasses.Empty();

    UE_LOG(LogModLoader, Warning, TEXT("Scanning Asset Registry for Vehicles... Found %d total assets in /Game/CarImports"), AssetDataList.Num());

	for (const FAssetData& Asset : AssetDataList)
	{
        // Debug Log every asset found
        UE_LOG(LogModLoader, Log, TEXT("Checking Asset: %s (%s)"), *Asset.AssetName.ToString(), *Asset.AssetClassPath.ToString());

		if (Asset.AssetName.ToString().StartsWith("BP_"))
		{
			FString ClassPath = Asset.GetObjectPathString() + "_C";
			UClass* LoadedClass = LoadObject<UClass>(NULL, *ClassPath);
			
			if (LoadedClass && LoadedClass->IsChildOf(AActor::StaticClass()))
			{
				LoadedVehicleClasses.Add(LoadedClass);
				UE_LOG(LogModLoader, Warning, TEXT("SUCCESS: Added Vehicle Class: %s"), *Asset.AssetName.ToString());
			}
		}
	}

    UE_LOG(LogModLoader, Warning, TEXT("Returning %d Vehicle Classes."), LoadedVehicleClasses.Num());
	return LoadedVehicleClasses;
}