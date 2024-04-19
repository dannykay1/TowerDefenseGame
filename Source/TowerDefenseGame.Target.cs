// Copyright Danny Kay 2024

using UnrealBuildTool;
using System.Collections.Generic;

public class TowerDefenseGameTarget : TargetRules
{
	public TowerDefenseGameTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "TowerDefenseGame" } );
	}
}
