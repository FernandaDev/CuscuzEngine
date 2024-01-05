project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"

   files { "Source/**.h", "Source/**.cpp" }

   includedirs
   {
      "Source",
      "Dependencies/SDL/include",
      --"Dependencies/SDL2_image/include",

	  -- Include Core
	  "../Core/Source"
   }

   libdirs
   { 
      "Dependencies/SDL2/lib",
      --"Dependencies/SDL2_image/lib" 
   } 

   links
   {
      "Core",
      "SDL2.lib",
      "SDL2main.lib",
      --"SDL2_image.lib",
   }

   local scriptDir = path.getdirectory(_SCRIPT)
   postbuildcommands 
   {
    '{COPY} ' .. path.join(scriptDir, 'SDL2.dll') .. ' "$(TargetDir)"',
    --'{COPY} ' .. path.join(scriptDir, 'SDL2_image.dll') .. ' "$(TargetDir)"'
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS" }

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