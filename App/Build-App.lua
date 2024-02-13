project "App"
   kind "ConsoleApp"
   language "C++"
   cppdialect "C++20"
   targetdir "Binaries/%{cfg.buildcfg}"
   staticruntime "off"  

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
      "Assets",
      "../GameCore/Source",
      "../CuscuzEngine/Source",

      "%{IncludeDir.SDL2}",
      "%{IncludeDir.SDL2_image}",
      "%{IncludeDir.ImGui}",
      "%{IncludeDir.glm}",

      "../Vendor/Log/include",
   }

   -- libdirs {} 

   links
   {
      "CuscuzEngine",
      "GameCore",
   }

   postbuildcommands 
   {
      '{COPYDIR} "' .. Engine_DLLs .. '" "$(TargetDir)"'
   }

   targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
   objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

   filter "system:windows"
       systemversion "latest"
       defines { "WINDOWS", "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING" }

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