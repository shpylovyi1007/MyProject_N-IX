// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class study : ModuleRules
{
	public study(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"study",
			"study/Variant_Platforming",
			"study/Variant_Platforming/Animation",
			"study/Variant_Combat",
			"study/Variant_Combat/AI",
			"study/Variant_Combat/Animation",
			"study/Variant_Combat/Gameplay",
			"study/Variant_Combat/Interfaces",
			"study/Variant_Combat/UI",
			"study/Variant_SideScrolling",
			"study/Variant_SideScrolling/AI",
			"study/Variant_SideScrolling/Gameplay",
			"study/Variant_SideScrolling/Interfaces",
			"study/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
