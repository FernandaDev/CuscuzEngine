-- premake5.lua
workspace "Game"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Engine"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "GameCore"
	include "GameCore/Build-GameCore.lua"
group ""

include "Engine/Build-Engine.lua"