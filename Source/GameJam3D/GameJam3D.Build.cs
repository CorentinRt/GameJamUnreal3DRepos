// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameJam3D : ModuleRules
{
	public GameJam3D(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
