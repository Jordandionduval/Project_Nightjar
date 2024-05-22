// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "Project_Nightjar/Project_NightjarGameMode.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeProject_NightjarGameMode() {}

// Begin Cross Module References
ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
PROJECT_NIGHTJAR_API UClass* Z_Construct_UClass_AProject_NightjarGameMode();
PROJECT_NIGHTJAR_API UClass* Z_Construct_UClass_AProject_NightjarGameMode_NoRegister();
UPackage* Z_Construct_UPackage__Script_Project_Nightjar();
// End Cross Module References

// Begin Class AProject_NightjarGameMode
void AProject_NightjarGameMode::StaticRegisterNativesAProject_NightjarGameMode()
{
}
IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(AProject_NightjarGameMode);
UClass* Z_Construct_UClass_AProject_NightjarGameMode_NoRegister()
{
	return AProject_NightjarGameMode::StaticClass();
}
struct Z_Construct_UClass_AProject_NightjarGameMode_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "Project_NightjarGameMode.h" },
		{ "ModuleRelativePath", "Project_NightjarGameMode.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AProject_NightjarGameMode>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_AProject_NightjarGameMode_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameModeBase,
	(UObject* (*)())Z_Construct_UPackage__Script_Project_Nightjar,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_NightjarGameMode_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AProject_NightjarGameMode_Statics::ClassParams = {
	&AProject_NightjarGameMode::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	0,
	0,
	0x008802ACu,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AProject_NightjarGameMode_Statics::Class_MetaDataParams), Z_Construct_UClass_AProject_NightjarGameMode_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AProject_NightjarGameMode()
{
	if (!Z_Registration_Info_UClass_AProject_NightjarGameMode.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AProject_NightjarGameMode.OuterSingleton, Z_Construct_UClass_AProject_NightjarGameMode_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AProject_NightjarGameMode.OuterSingleton;
}
template<> PROJECT_NIGHTJAR_API UClass* StaticClass<AProject_NightjarGameMode>()
{
	return AProject_NightjarGameMode::StaticClass();
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AProject_NightjarGameMode);
AProject_NightjarGameMode::~AProject_NightjarGameMode() {}
// End Class AProject_NightjarGameMode

// Begin Registration
struct Z_CompiledInDeferFile_FID_Users_joe_b_Documents_0_Projects_GameJam_Project_Nightjar_Project_Nightjar_Source_Project_Nightjar_Project_NightjarGameMode_h_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AProject_NightjarGameMode, AProject_NightjarGameMode::StaticClass, TEXT("AProject_NightjarGameMode"), &Z_Registration_Info_UClass_AProject_NightjarGameMode, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AProject_NightjarGameMode), 2970570717U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_Users_joe_b_Documents_0_Projects_GameJam_Project_Nightjar_Project_Nightjar_Source_Project_Nightjar_Project_NightjarGameMode_h_2066374566(TEXT("/Script/Project_Nightjar"),
	Z_CompiledInDeferFile_FID_Users_joe_b_Documents_0_Projects_GameJam_Project_Nightjar_Project_Nightjar_Source_Project_Nightjar_Project_NightjarGameMode_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_Users_joe_b_Documents_0_Projects_GameJam_Project_Nightjar_Project_Nightjar_Source_Project_Nightjar_Project_NightjarGameMode_h_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// End Registration
PRAGMA_ENABLE_DEPRECATION_WARNINGS
