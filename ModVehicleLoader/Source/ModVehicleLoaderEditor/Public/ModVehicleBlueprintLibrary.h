#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ModVehicleBlueprintLibrary.generated.h"

UCLASS()
class MODVEHICLELOADEREDITOR_API UModVehicleBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Opens a Windows File Dialog to pick an FBX */
	UFUNCTION(BlueprintCallable, Category = "Modding Tools")
	static void OpenModFileDialog(FString& OutFilePath, bool& bSuccess);

	/** Imports the vehicle from the path and sets up materials */
	UFUNCTION(BlueprintCallable, Category = "Modding Tools")
	static void ImportModVehicle(FString FilePath);
};