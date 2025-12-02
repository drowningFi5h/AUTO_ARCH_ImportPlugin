#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ModLoaderSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogModLoader, Log, All);

UCLASS()
class MODVEHICLELOADER_API UModLoaderSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	// Call this from Blueprint when the game starts or when the user presses "Refresh Mods"
	UFUNCTION(BlueprintCallable, Category = "Modding")
	void LoadMods();

	// Returns a list of all vehicle classes found in the loaded Paks
	UFUNCTION(BlueprintCallable, Category = "Modding")
	TArray<UClass*> GetLoadedVehicleClasses();

protected:
	void MountPakFile(const FString& PakPath);
	
	// Registry to keep track of loaded assets
	UPROPERTY()
	TArray<UClass*> LoadedVehicleClasses;
};