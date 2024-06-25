-- premake5.lua
workspace "CuscuzEngineProject"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "App"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

outputdir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"
engine_dlls = "../CuscuzEngine/Dependencies/DLL/"

includedir = {}
includedir["SDL2"] = "%{wks.location}/CuscuzEngine/Dependencies/SDL2/include"
includedir["glm"] = "%{wks.location}/CuscuzEngine/Dependencies/glm"
includedir["SDL2_image"] = "%{wks.location}/CuscuzEngine/Dependencies/SDL2_image/include"
includedir["SPD_Log"] = "%{wks.location}/Vendor/Log/include"
includedir["ImGui"] = "%{wks.location}/CuscuzEngine/Vendor/ImGui"
includedir["yaml"] = "%{wks.location}/CuscuzEngine/Vendor/yaml/include/yaml-cpp"

include "CuscuzEngine/Vendor/ImGui"
include "CuscuzEngine/Vendor/yaml"

include "CuscuzEngine/Build-CuscuzEngine.lua"
include "App/Build-App.lua"