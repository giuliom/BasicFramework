// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class GameProjectEditorTarget : TargetRules
{
	public GameProjectEditorTarget(TargetInfo Target) : base(Target)
	{
        DefaultBuildSettings = BuildSettingsVersion.V2;
        bOverrideBuildEnvironment = true;
        Type = TargetType.Editor;
        ExtraModuleNames.Add("BasicFramework");
        ExtraModuleNames.Add("GameProject");
	}
}
