// Copyright Danny Kay 2024

using UnrealBuildTool;
using System.Collections.Generic;

public class TowerDefenseGameEditorTarget : TargetRules
{
	public TowerDefenseGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V4;

		ExtraModuleNames.AddRange( new string[] { "TowerDefenseGame" } );
	}
}
