#include "ModVehicleLoaderEditor.h"
#include "ToolMenus.h"
#include "Misc/MessageDialog.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "LevelEditor.h"

#define LOCTEXT_NAMESPACE "FModVehicleLoaderEditorModule"

// Define a simple command class locally
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

	// The actual UI command
	TSharedPtr<FUICommandInfo> OpenPluginWindow;

	virtual void RegisterCommands() override
	{
		UI_COMMAND(OpenPluginWindow, "Import Vehicle", "Auto-Import FBX and setup Materials for Modding", EUserInterfaceActionType::Button, FInputChord());
	}
};

void FModVehicleLoaderEditorModule::StartupModule()
{
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

void FModVehicleLoaderEditorModule::PluginButtonClicked()
{
	// THIS IS WHERE WE WILL TRIGGER THE LOGIC LATER
	FText DialogText = FText::FromString("Success! The Mod Tools button is working.\n\nNext step: Connect FBX Import Logic.");
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FModVehicleLoaderEditorModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	// Extend the "LevelEditor.LevelEditorToolBar.PlayToolBar" section (or Main Toolbar)
	UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
	
	// Create a new section
	FToolMenuSection& Section = Menu->FindOrAddSection("ModdingTools");
	
	// Add the entry
	Section.AddEntry(FToolMenuEntry::InitToolBarButton(
		FModVehicleLoaderCommands::Get().OpenPluginWindow,
		FText::FromString("Mod Tools"), // Label Override
		FText::FromString("Click to import a mod vehicle"), // Tooltip
		FSlateIcon(FAppStyle::GetAppStyleSetName(), "LevelEditor.ImportScene") // Icon
	));
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModVehicleLoaderEditorModule, ModVehicleLoaderEditor)