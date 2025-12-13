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
				"ModVehicleLoader"
			}
		);

		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"UnrealEd",
				"AssetTools",
				"ContentBrowser",
				"Slate",
				"SlateCore",
				"ToolMenus",
				"LevelEditor",
				"EditorScriptingUtilities",
				"DesktopPlatform",
				"Blutility", 
				"UMGEditor" 
			}
		);
	}
}