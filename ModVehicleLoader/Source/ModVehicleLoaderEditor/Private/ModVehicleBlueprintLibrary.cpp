#include "ModVehicleBlueprintLibrary.h"
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h"
#include "AssetToolsModule.h"
#include "Factories/FbxFactory.h"
#include "AutomatedAssetImportData.h"
#include "Misc/MessageDialog.h"

void UModVehicleBlueprintLibrary::OpenModFileDialog(FString& OutFilePath, bool& bSuccess)
{
	bSuccess = false;

	if (!FModuleManager::Get().IsModuleLoaded("DesktopPlatform")) return;

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	if (DesktopPlatform)
	{
		TArray<FString> OpenFilenames;
		const bool bOpened = DesktopPlatform->OpenFileDialog(
			nullptr,
			TEXT("Select Vehicle FBX"),
			TEXT(""),
			TEXT(""),
			TEXT("FBX Files|*.fbx"),
			EFileDialogFlags::None,
			OpenFilenames
		);

		if (bOpened && OpenFilenames.Num() > 0)
		{
			OutFilePath = OpenFilenames[0];
			bSuccess = true;
		}
	}
}

void UModVehicleBlueprintLibrary::ImportModVehicle(FString FilePath)
{
	UE_LOG(LogTemp, Log, TEXT("Blueprint Import Started: %s"), *FilePath);

	// 1. Setup Import Data
	UAutomatedAssetImportData* ImportData = NewObject<UAutomatedAssetImportData>();
	ImportData->bReplaceExisting = true;
	ImportData->DestinationPath = TEXT("/Game/CarImports/Temp");
	ImportData->Filenames.Add(FilePath);
	ImportData->Factory = NewObject<UFbxFactory>();

	// 2. Import
	FAssetToolsModule& AssetToolsModule = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools");
	auto Assets = AssetToolsModule.Get().ImportAssetsAutomated(ImportData);

	// 3. Notify User
	if (Assets.Num() > 0)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Import Successful via Blueprint!"));
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Import Failed."));
	}
}