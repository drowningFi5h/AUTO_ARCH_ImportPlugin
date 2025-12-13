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
	UFUNCTION(BlueprintCallable, Category = "Modding")
	void LoadMods();

	// Return strictly Actor Classes so SpawnActor accepts them
	UFUNCTION(BlueprintCallable, Category = "Modding")
	TArray<TSubclassOf<AActor>> GetLoadedVehicleClasses();

protected:
	void MountPakFile(const FString& PakPath);
	
	// Registry to keep track of loaded assets
	UPROPERTY()
	TArray<TSubclassOf<AActor>> LoadedVehicleClasses;
};