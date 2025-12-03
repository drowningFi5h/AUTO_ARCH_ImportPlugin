using UnrealBuildTool;

public class ModVehicleLoaderEditor : ModuleRules
{
	public ModVehicleLoaderEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"ModVehicleLoader" // Link to our Runtime module
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd",        // REQUIRED: Main Editor functionality
				"AssetTools",      // REQUIRED: For FBX importing logic
				"ContentBrowser",  // For interacting with the content browser
				"Slate",           // UI Framework
				"SlateCore",       // UI Core
				"ToolMenus",       // For adding buttons to the toolbar
				"EditorScriptingUtilities", // Helper for automation tasks
				"DesktopPlatform", // For file dialogs
				"MainFrame"
			}
		);
	}
}