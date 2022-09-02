// Stay Tuned Up Game

using UnrealBuildTool;
using System.Collections.Generic;

public class StayTunedUpEditorTarget : TargetRules
{
	public StayTunedUpEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "StayTunedUp" } );
	}
}
