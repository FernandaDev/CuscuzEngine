project "ImGui"
	kind "StaticLib"
	language "C++"
    staticruntime "off"

	targetdir ("%{wks.location}/Binaries/" .. outputdir .. "/%{prj.name}")
   	objdir ("%{wks.location}/Binaries/Intermediates/" .. outputdir .. "/%{prj.name}")

	files
	{
		"ImGui/imconfig.h",
		"ImGui/imgui.h",
		"ImGui/imgui.cpp",
		"ImGui/imgui_draw.cpp",
		"ImGui/imgui_internal.h",
		"ImGui/imgui_tables.cpp",
		"ImGui/imgui_widgets.cpp",
		"ImGui/imstb_rectpack.h",
		"ImGui/imstb_textedit.h",
		"ImGui/imstb_truetype.h",
		"ImGui/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"
		cppdialect "C++17"

	filter "system:linux"
		pic "On"
		systemversion "latest"
		cppdialect "C++17"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"