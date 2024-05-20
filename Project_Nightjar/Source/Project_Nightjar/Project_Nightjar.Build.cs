// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Project_Nightjar : ModuleRules
{
	public Project_Nightjar(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
