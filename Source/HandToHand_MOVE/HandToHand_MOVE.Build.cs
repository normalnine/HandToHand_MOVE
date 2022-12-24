// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HandToHand_MOVE : ModuleRules
{
	public HandToHand_MOVE(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "NavigationSystem", "AIModule" });
	}
}
