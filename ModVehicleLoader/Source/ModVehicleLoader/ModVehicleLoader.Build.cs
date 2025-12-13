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
				"PakFile",          
				"Json",            
				"Projects",          
				"AssetRegistry" 
			}
		);
	}
}