// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ModLoaderSubsystem.h"
#include "Engine/GameInstance.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeModLoaderSubsystem() {}

// ********** Begin Cross Module References ********************************************************
COREUOBJECT_API UClass* Z_Construct_UClass_UClass();
ENGINE_API UClass* Z_Construct_UClass_AActor_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
MODVEHICLELOADER_API UClass* Z_Construct_UClass_UModLoaderSubsystem();
MODVEHICLELOADER_API UClass* Z_Construct_UClass_UModLoaderSubsystem_NoRegister();
UPackage* Z_Construct_UPackage__Script_ModVehicleLoader();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UModLoaderSubsystem Function GetLoadedVehicleClasses *********************
struct Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics
{
	struct ModLoaderSubsystem_eventGetLoadedVehicleClasses_Parms
	{
		TArray<TSubclassOf<AActor>> ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Modding" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Return strictly Actor Classes so SpawnActor accepts them\n" },
#endif
		{ "ModuleRelativePath", "Public/ModLoaderSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Return strictly Actor Classes so SpawnActor accepts them" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_ReturnValue_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0014000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ModLoaderSubsystem_eventGetLoadedVehicleClasses_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::NewProp_ReturnValue_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UModLoaderSubsystem, nullptr, "GetLoadedVehicleClasses", Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::PropPointers), sizeof(Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::ModLoaderSubsystem_eventGetLoadedVehicleClasses_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::Function_MetaDataParams), Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::ModLoaderSubsystem_eventGetLoadedVehicleClasses_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UModLoaderSubsystem::execGetLoadedVehicleClasses)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(TArray<TSubclassOf<AActor>>*)Z_Param__Result=P_THIS->GetLoadedVehicleClasses();
	P_NATIVE_END;
}
// ********** End Class UModLoaderSubsystem Function GetLoadedVehicleClasses ***********************

// ********** Begin Class UModLoaderSubsystem Function LoadMods ************************************
struct Z_Construct_UFunction_UModLoaderSubsystem_LoadMods_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Modding" },
		{ "ModuleRelativePath", "Public/ModLoaderSubsystem.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UModLoaderSubsystem_LoadMods_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UModLoaderSubsystem, nullptr, "LoadMods", nullptr, 0, 0, RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UModLoaderSubsystem_LoadMods_Statics::Function_MetaDataParams), Z_Construct_UFunction_UModLoaderSubsystem_LoadMods_Statics::Function_MetaDataParams)},  };
UFunction* Z_Construct_UFunction_UModLoaderSubsystem_LoadMods()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UModLoaderSubsystem_LoadMods_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UModLoaderSubsystem::execLoadMods)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	P_THIS->LoadMods();
	P_NATIVE_END;
}
// ********** End Class UModLoaderSubsystem Function LoadMods **************************************

// ********** Begin Class UModLoaderSubsystem ******************************************************
void UModLoaderSubsystem::StaticRegisterNativesUModLoaderSubsystem()
{
	UClass* Class = UModLoaderSubsystem::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetLoadedVehicleClasses", &UModLoaderSubsystem::execGetLoadedVehicleClasses },
		{ "LoadMods", &UModLoaderSubsystem::execLoadMods },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UModLoaderSubsystem;
UClass* UModLoaderSubsystem::GetPrivateStaticClass()
{
	using TClass = UModLoaderSubsystem;
	if (!Z_Registration_Info_UClass_UModLoaderSubsystem.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ModLoaderSubsystem"),
			Z_Registration_Info_UClass_UModLoaderSubsystem.InnerSingleton,
			StaticRegisterNativesUModLoaderSubsystem,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_UModLoaderSubsystem.InnerSingleton;
}
UClass* Z_Construct_UClass_UModLoaderSubsystem_NoRegister()
{
	return UModLoaderSubsystem::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UModLoaderSubsystem_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "ModLoaderSubsystem.h" },
		{ "ModuleRelativePath", "Public/ModLoaderSubsystem.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_LoadedVehicleClasses_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Registry to keep track of loaded assets\n" },
#endif
		{ "ModuleRelativePath", "Public/ModLoaderSubsystem.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Registry to keep track of loaded assets" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FClassPropertyParams NewProp_LoadedVehicleClasses_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_LoadedVehicleClasses;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UModLoaderSubsystem_GetLoadedVehicleClasses, "GetLoadedVehicleClasses" }, // 2509161610
		{ &Z_Construct_UFunction_UModLoaderSubsystem_LoadMods, "LoadMods" }, // 3442911583
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UModLoaderSubsystem>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FClassPropertyParams Z_Construct_UClass_UModLoaderSubsystem_Statics::NewProp_LoadedVehicleClasses_Inner = { "LoadedVehicleClasses", nullptr, (EPropertyFlags)0x0004000000000000, UECodeGen_Private::EPropertyGenFlags::Class, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UClass_UClass, Z_Construct_UClass_AActor_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UClass_UModLoaderSubsystem_Statics::NewProp_LoadedVehicleClasses = { "LoadedVehicleClasses", nullptr, (EPropertyFlags)0x0024080000000000, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UModLoaderSubsystem, LoadedVehicleClasses), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_LoadedVehicleClasses_MetaData), NewProp_LoadedVehicleClasses_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UModLoaderSubsystem_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UModLoaderSubsystem_Statics::NewProp_LoadedVehicleClasses_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UModLoaderSubsystem_Statics::NewProp_LoadedVehicleClasses,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UModLoaderSubsystem_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UModLoaderSubsystem_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
	(UObject* (*)())Z_Construct_UPackage__Script_ModVehicleLoader,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UModLoaderSubsystem_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UModLoaderSubsystem_Statics::ClassParams = {
	&UModLoaderSubsystem::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UModLoaderSubsystem_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UModLoaderSubsystem_Statics::PropPointers),
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UModLoaderSubsystem_Statics::Class_MetaDataParams), Z_Construct_UClass_UModLoaderSubsystem_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UModLoaderSubsystem()
{
	if (!Z_Registration_Info_UClass_UModLoaderSubsystem.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UModLoaderSubsystem.OuterSingleton, Z_Construct_UClass_UModLoaderSubsystem_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UModLoaderSubsystem.OuterSingleton;
}
UModLoaderSubsystem::UModLoaderSubsystem() {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UModLoaderSubsystem);
UModLoaderSubsystem::~UModLoaderSubsystem() {}
// ********** End Class UModLoaderSubsystem ********************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h__Script_ModVehicleLoader_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UModLoaderSubsystem, UModLoaderSubsystem::StaticClass, TEXT("UModLoaderSubsystem"), &Z_Registration_Info_UClass_UModLoaderSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UModLoaderSubsystem), 2910857737U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h__Script_ModVehicleLoader_3529930031(TEXT("/Script/ModVehicleLoader"),
	Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h__Script_ModVehicleLoader_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoader_Public_ModLoaderSubsystem_h__Script_ModVehicleLoader_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
