// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GameProjectTarget : TargetRules
{
	public GameProjectTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        ExtraModuleNames.Add("BasicFramework");
        ExtraModuleNames.Add("GameProject");
	}
}
