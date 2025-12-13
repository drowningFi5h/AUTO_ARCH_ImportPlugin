#include "ModVehicleLoaderEditor.h"
#include "ToolMenus.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "LevelEditor.h"

#include "EditorUtilitySubsystem.h"
#include "EditorUtilityWidgetBlueprint.h"
#include "Editor.h" // For GEditor

#define LOCTEXT_NAMESPACE "FModVehicleLoaderEditorModule"

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
		UI_COMMAND(OpenPluginWindow, "Import Vehicle", "Launch the Mod Importer Tool", EUserInterfaceActionType::Button, FInputChord());
	}
};

void FModVehicleLoaderEditorModule::StartupModule()
{
    UE_LOG(LogTemp, Error, TEXT("ModVehicleLoaderEditorModule::StartupModule Executing..."));

	FModVehicleLoaderCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FModVehicleLoaderCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FModVehicleLoaderEditorModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FModVehicleLoaderEditorModule::RegisterMenus));
    FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
    LevelEditorModule.GetGlobalLevelEditorActions()->Append(PluginCommands.ToSharedRef());
}

void FModVehicleLoaderEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FModVehicleLoaderCommands::Unregister();
}

void FModVehicleLoaderEditorModule::RegisterMenus()
{
    UE_LOG(LogTemp, Error, TEXT("ModVehicleLoaderEditorModule::RegisterMenus Executing..."));

	FToolMenuOwnerScoped OwnerScoped(this);
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	FToolMenuSection& Section = Menu->FindOrAddSection("ModdingTools");
	
	Section.AddEntry(FToolMenuEntry::InitToolBarButton(
		FModVehicleLoaderCommands::Get().OpenPluginWindow,
		FText::FromString("Mod Tool"), // Shortened name
		FText::FromString("Launch the Mod Importer Utility"),
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.ImportScene")
	));
}

void FModVehicleLoaderEditorModule::PluginButtonClicked()
{
    UE_LOG(LogTemp, Error, TEXT(">>> TOOLBAR BUTTON CLICKED! <<<"));

    // In Unreal paths, Content folder = /Game/
    FString WidgetPath = TEXT("/Game/test/EUW_ModImporter.EUW_ModImporter");

    UE_LOG(LogTemp, Warning, TEXT("Attempting to load widget at: %s"), *WidgetPath);

    // 2. Load the Asset
    UObject* LoadedAsset = LoadObject<UObject>(nullptr, *WidgetPath);
    
    if (!LoadedAsset)
    {
        UE_LOG(LogTemp, Error, TEXT("Could not find EUW_ModImporter! Object is NULL. Check path: %s"), *WidgetPath);
        FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Error: Could not find EUW_ModImporter in /Game/test/. Did you move it?"));
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("Asset found: %s. Casting to EditorUtilityWidgetBlueprint..."), *LoadedAsset->GetName());

    // 3. Cast and Spawn
    if (UEditorUtilityWidgetBlueprint* WidgetBP = Cast<UEditorUtilityWidgetBlueprint>(LoadedAsset))
    {
        UEditorUtilitySubsystem* EditorUtilitySubsystem = GEditor->GetEditorSubsystem<UEditorUtilitySubsystem>();
        if (EditorUtilitySubsystem)
        {
            EditorUtilitySubsystem->SpawnAndRegisterTab(WidgetBP);
            UE_LOG(LogTemp, Error, TEXT("SUCCESS: Widget Spawned."));
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("FAILED to get EditorUtilitySubsystem."));
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Found asset, but it is NOT an Editor Utility Widget Blueprint. Actual Class: %s"), *LoadedAsset->GetClass()->GetName());
    }
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModVehicleLoaderEditorModule, ModVehicleLoaderEditor)