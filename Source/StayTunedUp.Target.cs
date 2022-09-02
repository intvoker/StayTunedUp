// Stay Tuned Up Game

using UnrealBuildTool;
using System.Collections.Generic;

public class StayTunedUpTarget : TargetRules
{
	public StayTunedUpTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "StayTunedUp" } );
	}
}
