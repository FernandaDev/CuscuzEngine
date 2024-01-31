-- premake5.lua
workspace "Game"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
Engine_DLLs = "../CuscuzEngine/Dependencies/DLL/"

IncludeDir = {}
IncludeDir["SDL2"] = "%{wks.location}/CuscuzEngine/Dependencies/SDL2/include"
IncludeDir["SDL2_image"] = "%{wks.location}/CuscuzEngine/Dependencies/SDL2_image/include"
IncludeDir["SPD_Log"] = "%{wks.location}/Vendor/Log/include"
IncludeDir["ImGui"] = "%{wks.location}/CuscuzEngine/Vendor/ImGui"

include "CuscuzEngine/Vendor/ImGui"

include "GameCore/Build-GameCore.lua"
include "CuscuzEngine/Build-CuscuzEngine.lua"
include "App/Build-App.lua"