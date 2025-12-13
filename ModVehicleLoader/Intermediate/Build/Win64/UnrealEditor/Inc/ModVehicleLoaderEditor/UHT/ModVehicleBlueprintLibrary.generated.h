// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ModVehicleBlueprintLibrary.h"

#ifdef MODVEHICLELOADEREDITOR_ModVehicleBlueprintLibrary_generated_h
#error "ModVehicleBlueprintLibrary.generated.h already included, missing '#pragma once' in ModVehicleBlueprintLibrary.h"
#endif
#define MODVEHICLELOADEREDITOR_ModVehicleBlueprintLibrary_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

// ********** Begin Class UModVehicleBlueprintLibrary **********************************************
#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execPackModPlugin); \
	DECLARE_FUNCTION(execImportModVehicle); \
	DECLARE_FUNCTION(execOpenModFileDialog);


MODVEHICLELOADEREDITOR_API UClass* Z_Construct_UClass_UModVehicleBlueprintLibrary_NoRegister();

#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_10_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUModVehicleBlueprintLibrary(); \
	friend struct Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MODVEHICLELOADEREDITOR_API UClass* Z_Construct_UClass_UModVehicleBlueprintLibrary_NoRegister(); \
public: \
	DECLARE_CLASS2(UModVehicleBlueprintLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ModVehicleLoaderEditor"), Z_Construct_UClass_UModVehicleBlueprintLibrary_NoRegister) \
	DECLARE_SERIALIZER(UModVehicleBlueprintLibrary)


#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_10_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UModVehicleBlueprintLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UModVehicleBlueprintLibrary(UModVehicleBlueprintLibrary&&) = delete; \
	UModVehicleBlueprintLibrary(const UModVehicleBlueprintLibrary&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UModVehicleBlueprintLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UModVehicleBlueprintLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UModVehicleBlueprintLibrary) \
	NO_API virtual ~UModVehicleBlueprintLibrary();


#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_7_PROLOG
#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_10_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_10_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_10_INCLASS_NO_PURE_DECLS \
	FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h_10_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UModVehicleBlueprintLibrary;

// ********** End Class UModVehicleBlueprintLibrary ************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
