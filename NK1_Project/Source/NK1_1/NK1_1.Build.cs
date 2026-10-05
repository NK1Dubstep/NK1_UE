// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NK1_1 : ModuleRules
{
	public NK1_1(ReadOnlyTargetRules Target) : base(Target)
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
			"NK1_1",
			"NK1_1/Variant_Platforming",
			"NK1_1/Variant_Platforming/Animation",
			"NK1_1/Variant_Combat",
			"NK1_1/Variant_Combat/AI",
			"NK1_1/Variant_Combat/Animation",
			"NK1_1/Variant_Combat/Gameplay",
			"NK1_1/Variant_Combat/Interfaces",
			"NK1_1/Variant_Combat/UI",
			"NK1_1/Variant_SideScrolling",
			"NK1_1/Variant_SideScrolling/AI",
			"NK1_1/Variant_SideScrolling/Gameplay",
			"NK1_1/Variant_SideScrolling/Interfaces",
			"NK1_1/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
