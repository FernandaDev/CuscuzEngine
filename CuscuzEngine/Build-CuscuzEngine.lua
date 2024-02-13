project "CuscuzEngine"
   kind "StaticLib"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   pchheader "pch.h"
   pchsource "Source/pch.cpp"

   files 
   {
      "Source/**.h", 
      "Source/**.cpp",
      "%{IncludeDir.glm}/**.hpp",
      "%{IncludeDir.glm}/**.inl",
   }

   includedirs
   {
      "Source",
      "Dependencies/SDL2/include",
      "Dependencies/SDL2_image/include",
      "Vendor/ImGui",
      
      "%{IncludeDir.SPD_Log}",
      "%{IncludeDir.glm}",
   }

   libdirs
   { 
      "Dependencies/SDL2/lib",
      "Dependencies/SDL2_image/lib" 
   } 

   links
   {
      "ImGui",
      "SDL2.lib",
      "SDL2main.lib",
      "SDL2_image.lib",
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS", "_SILENCE_ALL_MS_EXT_DEPRECATION_WARNINGS" }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"