// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NYNS_GameJam_Project : ModuleRules
{
	public NYNS_GameJam_Project(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput", "MoviePlayer" });
	}
}
