#include "ModVehicleLoader.h"

#define LOCTEXT_NAMESPACE "FModVehicleLoaderModule"

void FModVehicleLoaderModule::StartupModule()
{
	// This code will execute after our module is loaded into memory
}

void FModVehicleLoaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up our module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FModVehicleLoaderModule, ModVehicleLoader)	