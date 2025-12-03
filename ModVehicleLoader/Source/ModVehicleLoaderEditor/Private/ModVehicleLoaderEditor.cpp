#include "ModVehicleLoaderEditor.h"
#include "ToolMenus.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "LevelEditor.h"

// --- FIX: Use direct includes without the 'DesktopPlatform/Public/' prefix ---
#include "IDesktopPlatform.h"
#include "DesktopPlatformModule.h" 

#include "AssetToolsModule.h"
#include "Factories/FbxFactory.h"
#include "AutomatedAssetImportData.h"

#define LOCTEXT_NAMESPACE "FModVehicleLoaderEditorModule"

// Define the UI Command
class FModVehicleLoaderCommands : public TCommands<FModVehicleLoaderCommands>
{
public:
	FModVehicleLoaderCommands()
		: TCommands<FModVehicleLoaderCommands>(
			TEXT("ModVehicleLoader"), 
			NSLOCTEXT("Contexts", "ModVehicleLoader", "Mod Vehicle Loader Plugin"), 
			NAME_None, 
			FAppStyle::GetAppStyleSetName())
	{}

	TSharedPtr<FUICommandInfo> OpenPluginWindow;

	virtual void RegisterCommands() override
	{
		UI_COMMAND(OpenPluginWindow, "Import Vehicle", "Select an FBX to create a Mod Vehicle", EUserInterfaceActionType::Button, FInputChord());
	}
};

void FModVehicleLoaderEditorModule::StartupModule()
{
    // Ensure DesktopPlatform is loaded explicitly
    if (!FModuleManager::Get().IsModuleLoaded(TEXT("DesktopPlatform")))
    {
        FModuleManager::Get().LoadModule(TEXT("DesktopPlatform"));
    }
    
	// 1. Register the Command
	FModVehicleLoaderCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FModVehicleLoaderCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FModVehicleLoaderEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	// 2. Add to the Toolbar using UToolMenus
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FModVehicleLoaderEditorModule::RegisterMenus));
}

void FModVehicleLoaderEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FModVehicleLoaderCommands::Unregister();
}

void FModVehicleLoaderEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	FToolMenuSection& Section = Menu->FindOrAddSection("ModdingTools");
	
	Section.AddEntry(FToolMenuEntry::InitToolBarButton(
		FModVehicleLoaderCommands::Get().OpenPluginWindow,
		FText::FromString("Import Vehicle"),
		FText::FromString("Import FBX and Create Mod"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.ImportScene")
	));
}

void FModVehicleLoaderEditorModule::PluginButtonClicked()
{
    // Ensure the module is available
    if (!FModuleManager::Get().IsModuleLoaded(TEXT("DesktopPlatform")))
    {
        UE_LOG(LogTemp, Error, TEXT("DesktopPlatform Module is not loaded. Cannot open file dialog."));
        return;
    }

	IDesktopPlatform* DesktopPlatform = FDesktopPlatformModule::Get();
	
	if (DesktopPlatform) 
	{
        UE_LOG(LogTemp, Log, TEXT("DesktopPlatform initialized. Attempting to open file dialog."));
        
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
			ImportVehicleFromFBX(OpenFilenames[0]);
		}
	}
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Failed to retrieve IDesktopPlatform interface. Dialog failed to open."));
    }
}

void FModVehicleLoaderEditorModule::ImportVehicleFromFBX(const FString& FilePath)
{
	UE_LOG(LogTemp, Log, TEXT("Starting Import for: %s"), *FilePath);

	UAutomatedAssetImportData* ImportData = NewObject<UAutomatedAssetImportData>();
	ImportData->bReplaceExisting = true;
	ImportData->DestinationPath = TEXT("/Game/CarImports/Temp"); 
	ImportData->Filenames.Add(FilePath);

	UFbxFactory* FbxFactory = NewObject<UFbxFactory>();
	ImportData->Factory = FbxFactory;

	FAssetToolsModule& AssetToolsModule = FModuleManager::Get().LoadModuleChecked<FAssetToolsModule>("AssetTools");
	TArray<UObject*> ImportedAssets = AssetToolsModule.Get().ImportAssetsAutomated(ImportData);

	if (ImportedAssets.Num() > 0)
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Import Successful! Check Content/CarImports/Temp"));
		ProcessImportedAssets(ImportedAssets);
	}
	else
	{
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Import Failed or Cancelled. Check Output Log for details."));
	}
}

void FModVehicleLoaderEditorModule::ProcessImportedAssets(const TArray<UObject*>& ImportedAssets)
{
	for (UObject* Asset : ImportedAssets)
	{
		UE_LOG(LogTemp, Warning, TEXT("Imported Asset: %s"), *Asset->GetName());
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModVehicleLoaderEditorModule, ModVehicleLoaderEditor)