// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ModVehicleBlueprintLibrary.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeModVehicleBlueprintLibrary() {}

// ********** Begin Cross Module References ********************************************************
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
MODVEHICLELOADEREDITOR_API UClass* Z_Construct_UClass_UModVehicleBlueprintLibrary();
MODVEHICLELOADEREDITOR_API UClass* Z_Construct_UClass_UModVehicleBlueprintLibrary_NoRegister();
UPackage* Z_Construct_UPackage__Script_ModVehicleLoaderEditor();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UModVehicleBlueprintLibrary Function ImportModVehicle ********************
struct Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics
{
	struct ModVehicleBlueprintLibrary_eventImportModVehicle_Parms
	{
		FString FilePath;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Modding Tools" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Imports the vehicle from the path\n" },
#endif
		{ "ModuleRelativePath", "Public/ModVehicleBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Imports the vehicle from the path" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_FilePath;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::NewProp_FilePath = { "FilePath", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ModVehicleBlueprintLibrary_eventImportModVehicle_Parms, FilePath), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::NewProp_FilePath,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UModVehicleBlueprintLibrary, nullptr, "ImportModVehicle", Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::PropPointers), sizeof(Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::ModVehicleBlueprintLibrary_eventImportModVehicle_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::Function_MetaDataParams), Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::ModVehicleBlueprintLibrary_eventImportModVehicle_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UModVehicleBlueprintLibrary::execImportModVehicle)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_FilePath);
	P_FINISH;
	P_NATIVE_BEGIN;
	UModVehicleBlueprintLibrary::ImportModVehicle(Z_Param_FilePath);
	P_NATIVE_END;
}
// ********** End Class UModVehicleBlueprintLibrary Function ImportModVehicle **********************

// ********** Begin Class UModVehicleBlueprintLibrary Function OpenModFileDialog *******************
struct Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics
{
	struct ModVehicleBlueprintLibrary_eventOpenModFileDialog_Parms
	{
		FString OutFilePath;
		bool bSuccess;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Modding Tools" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Opens a Windows File Dialog to pick an FBX\n" },
#endif
		{ "ModuleRelativePath", "Public/ModVehicleBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Opens a Windows File Dialog to pick an FBX" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_OutFilePath;
	static void NewProp_bSuccess_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::NewProp_OutFilePath = { "OutFilePath", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ModVehicleBlueprintLibrary_eventOpenModFileDialog_Parms, OutFilePath), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::NewProp_bSuccess_SetBit(void* Obj)
{
	((ModVehicleBlueprintLibrary_eventOpenModFileDialog_Parms*)Obj)->bSuccess = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(ModVehicleBlueprintLibrary_eventOpenModFileDialog_Parms), &Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::NewProp_OutFilePath,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::NewProp_bSuccess,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UModVehicleBlueprintLibrary, nullptr, "OpenModFileDialog", Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::PropPointers), sizeof(Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::ModVehicleBlueprintLibrary_eventOpenModFileDialog_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::Function_MetaDataParams), Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::ModVehicleBlueprintLibrary_eventOpenModFileDialog_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UModVehicleBlueprintLibrary::execOpenModFileDialog)
{
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_OutFilePath);
	P_GET_UBOOL_REF(Z_Param_Out_bSuccess);
	P_FINISH;
	P_NATIVE_BEGIN;
	UModVehicleBlueprintLibrary::OpenModFileDialog(Z_Param_Out_OutFilePath,Z_Param_Out_bSuccess);
	P_NATIVE_END;
}
// ********** End Class UModVehicleBlueprintLibrary Function OpenModFileDialog *********************

// ********** Begin Class UModVehicleBlueprintLibrary Function PackModPlugin ***********************
struct Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics
{
	struct ModVehicleBlueprintLibrary_eventPackModPlugin_Parms
	{
		FString PluginName;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Modding Tools" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Packs the mod/plugin into a .pak file\n" },
#endif
		{ "ModuleRelativePath", "Public/ModVehicleBlueprintLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Packs the mod/plugin into a .pak file" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_PluginName;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::NewProp_PluginName = { "PluginName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ModVehicleBlueprintLibrary_eventPackModPlugin_Parms, PluginName), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::NewProp_PluginName,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UModVehicleBlueprintLibrary, nullptr, "PackModPlugin", Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::PropPointers), sizeof(Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::ModVehicleBlueprintLibrary_eventPackModPlugin_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::Function_MetaDataParams), Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::ModVehicleBlueprintLibrary_eventPackModPlugin_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UModVehicleBlueprintLibrary::execPackModPlugin)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_PluginName);
	P_FINISH;
	P_NATIVE_BEGIN;
	UModVehicleBlueprintLibrary::PackModPlugin(Z_Param_PluginName);
	P_NATIVE_END;
}
// ********** End Class UModVehicleBlueprintLibrary Function PackModPlugin *************************

// ********** Begin Class UModVehicleBlueprintLibrary **********************************************
void UModVehicleBlueprintLibrary::StaticRegisterNativesUModVehicleBlueprintLibrary()
{
	UClass* Class = UModVehicleBlueprintLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "ImportModVehicle", &UModVehicleBlueprintLibrary::execImportModVehicle },
		{ "OpenModFileDialog", &UModVehicleBlueprintLibrary::execOpenModFileDialog },
		{ "PackModPlugin", &UModVehicleBlueprintLibrary::execPackModPlugin },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UModVehicleBlueprintLibrary;
UClass* UModVehicleBlueprintLibrary::GetPrivateStaticClass()
{
	using TClass = UModVehicleBlueprintLibrary;
	if (!Z_Registration_Info_UClass_UModVehicleBlueprintLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("ModVehicleBlueprintLibrary"),
			Z_Registration_Info_UClass_UModVehicleBlueprintLibrary.InnerSingleton,
			StaticRegisterNativesUModVehicleBlueprintLibrary,
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
	return Z_Registration_Info_UClass_UModVehicleBlueprintLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UModVehicleBlueprintLibrary_NoRegister()
{
	return UModVehicleBlueprintLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "ModVehicleBlueprintLibrary.h" },
		{ "ModuleRelativePath", "Public/ModVehicleBlueprintLibrary.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UModVehicleBlueprintLibrary_ImportModVehicle, "ImportModVehicle" }, // 4151589019
		{ &Z_Construct_UFunction_UModVehicleBlueprintLibrary_OpenModFileDialog, "OpenModFileDialog" }, // 3041937281
		{ &Z_Construct_UFunction_UModVehicleBlueprintLibrary_PackModPlugin, "PackModPlugin" }, // 3990792380
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UModVehicleBlueprintLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_ModVehicleLoaderEditor,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics::ClassParams = {
	&UModVehicleBlueprintLibrary::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x001000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UModVehicleBlueprintLibrary()
{
	if (!Z_Registration_Info_UClass_UModVehicleBlueprintLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UModVehicleBlueprintLibrary.OuterSingleton, Z_Construct_UClass_UModVehicleBlueprintLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UModVehicleBlueprintLibrary.OuterSingleton;
}
UModVehicleBlueprintLibrary::UModVehicleBlueprintLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UModVehicleBlueprintLibrary);
UModVehicleBlueprintLibrary::~UModVehicleBlueprintLibrary() {}
// ********** End Class UModVehicleBlueprintLibrary ************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h__Script_ModVehicleLoaderEditor_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UModVehicleBlueprintLibrary, UModVehicleBlueprintLibrary::StaticClass, TEXT("UModVehicleBlueprintLibrary"), &Z_Registration_Info_UClass_UModVehicleBlueprintLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UModVehicleBlueprintLibrary), 1180195436U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h__Script_ModVehicleLoaderEditor_4189951226(TEXT("/Script/ModVehicleLoaderEditor"),
	Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h__Script_ModVehicleLoaderEditor_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_AUTO_ARCH_PAK_EXPORT_Plugins_ModVehicleLoader_Source_ModVehicleLoaderEditor_Public_ModVehicleBlueprintLibrary_h__Script_ModVehicleLoaderEditor_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
