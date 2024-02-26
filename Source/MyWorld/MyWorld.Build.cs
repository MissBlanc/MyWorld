// Copyright Epic Games, Inc. All Rights Reserved.

using System.Collections.Generic;
using System.IO;
using UnrealBuildTool;

public class MyWorld : ModuleRules
{
	public MyWorld(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });

		PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        AddIncludePath(ref PrivateIncludePaths, "MyWorld");
    }

    void AddIncludePath(ref List<string> inPathList, string inRootDir)
    {
        inPathList.Add(inRootDir);

        string sourceDir = ModuleDirectory + "/../";
        string rootDirFullPath = sourceDir + inRootDir;

        AddIncludePathRecursive(ref inPathList, rootDirFullPath, sourceDir.Length);
    }

    void AddIncludePathRecursive(ref List<string> inPathList, string inRootDir, int inSplitLength)
    {
        foreach (string dir in Directory.GetDirectories(inRootDir))
        {
            string regDir = dir.Substring(inSplitLength).Replace('\\', '/');
            if (false == inPathList.Contains(regDir))
            {
                inPathList.Add(regDir);
            }

            AddIncludePathRecursive(ref inPathList, dir, inSplitLength);
        }
    }

    void LogPrintForTest()
    {
        foreach (var _path in PrivateIncludePaths)
        {
            System.Console.WriteLine("MyWorld.Build.cs : PrivateIncludePaths : {0}", _path);
        }
    }
}
