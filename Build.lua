-- premake5.lua
workspace "Game"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
Engine_DLLs = "../MyLittleEngine/Dependencies/DLL/"

include "GameCore/Build-GameCore.lua"
include "MyLittleEngine/Build-MyLittleEngine.lua"
include "App/Build-App.lua"