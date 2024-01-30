-- premake5.lua
workspace "Game"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "MyLittleEngine"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

IncludeDir = {}
IncludeDir["SDL2"] = "%{wks.location}/MyLittleEngine/Vendor/SDL2/include"

include "GameCore/Build-GameCore.lua"

include "MyLittleEngine/Build-MyLittleEngine.lua"