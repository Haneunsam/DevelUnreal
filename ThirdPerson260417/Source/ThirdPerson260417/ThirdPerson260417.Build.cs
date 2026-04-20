// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ThirdPerson260417 : ModuleRules
{
	public ThirdPerson260417(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
