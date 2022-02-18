// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class UncoExample : ModuleRules
{
    public UncoExample(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		// コルーチンにはC++20が必要
		CppStandard = CppStandardVersion.Cpp20;

		PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject", 
            "Engine",
            "InputCore", 
            "UnrealCoroutine" });
    }
}
