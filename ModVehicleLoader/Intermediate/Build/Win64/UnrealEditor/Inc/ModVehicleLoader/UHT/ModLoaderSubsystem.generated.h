// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "ModLoaderSubsystem.h"

#ifdef MODVEHICLELOADER_ModLoaderSubsystem_generated_h
#error "ModLoaderSubsystem.generated.h already included, missing '#pragma once' in ModLoaderSubsystem.h"
#endif
#define MODVEHICLELOADER_ModLoaderSubsystem_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class AActor;

// ********** Begin Class UModLoaderSubsystem ******************************************************
#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetLoadedVehicleClasses); \
	DECLARE_FUNCTION(execLoadMods);


MODVEHICLELOADER_API UClass* Z_Construct_UClass_UModLoaderSubsystem_NoRegister();

#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_12_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUModLoaderSubsystem(); \
	friend struct Z_Construct_UClass_UModLoaderSubsystem_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend MODVEHICLELOADER_API UClass* Z_Construct_UClass_UModLoaderSubsystem_NoRegister(); \
public: \
	DECLARE_CLASS2(UModLoaderSubsystem, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/ModVehicleLoader"), Z_Construct_UClass_UModLoaderSubsystem_NoRegister) \
	DECLARE_SERIALIZER(UModLoaderSubsystem)


#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_12_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UModLoaderSubsystem(); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UModLoaderSubsystem(UModLoaderSubsystem&&) = delete; \
	UModLoaderSubsystem(const UModLoaderSubsystem&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UModLoaderSubsystem); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UModLoaderSubsystem); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UModLoaderSubsystem) \
	NO_API virtual ~UModLoaderSubsystem();


#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_9_PROLOG
#define FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_12_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_12_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_12_INCLASS_NO_PURE_DECLS \
	FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h_12_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UModLoaderSubsystem;

// ********** End Class UModLoaderSubsystem ********************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
