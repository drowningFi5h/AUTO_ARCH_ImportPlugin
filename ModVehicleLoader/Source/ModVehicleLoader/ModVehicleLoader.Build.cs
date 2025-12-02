using UnrealBuildTool;

public class ModVehicleLoader : ModuleRules
{
	public ModVehicleLoader(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"PakFile",          // REQUIRED for .pak loading
				"Json",             // Useful for metadata
				"Projects",          // For IPluginManager
				"AssetRegistry"    // For asset discovery
			}
		);
	}
}