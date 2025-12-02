#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "Framework/Commands/Commands.h"

class FModVehicleLoaderEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	// This function runs when the user clicks the toolbar button
	void PluginButtonClicked();

private:
	void RegisterMenus();
	TSharedPtr<class FUICommandList> PluginCommands;
};