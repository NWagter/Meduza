workspace "Meduza"

	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release"
	}
	platforms { "x64" }
	
	filter "platforms:x64*"
		architecture "x64"
		system "windows"
	
outputDir = "%{cfg.buildcfg}-%{cfg.platform}"

project "Meduza"
	location "Meduza"
	kind "StaticLib"
	language "C++"
	
	warnings "Extra"
	flags { "FatalWarnings" }
	
	targetdir ("Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputDir .. "/%{prj.name}")

	pchheader "mePch.h"
	pchsource "%{prj.name}/Source/mePch.cpp"

	files
	{
		"%{prj.name}/Include/**.h",
		"%{prj.name}/Source/**.cpp",		
		"%{prj.name}/External/ImGui/**.cpp",
		"%{prj.name}/External/stb_image/**.cpp",
		"%{prj.name}/External/Glad/**.c"
	}

	includedirs
	{
		"$(SolutionDir)%{prj.name}/Include",
		"$(SolutionDir)%{prj.name}/Include/Core",
		"$(SolutionDir)%{prj.name}/External",
		"$(SolutionDir)%{prj.name}/External/stb_image",
		"$(SolutionDir)%{prj.name}/External/Dx12",		
		"$(SolutionDir)%{prj.name}/External/ImGui",
		"$(SolutionDir)%{prj.name}/External/Glad/include"
	}
	
	filter {"files:**/Glad/**.c"}
		flags { "NoPCH" }
		
	filter { "files:**/ImGui/**.cpp"}
		flags { "NoPCH" }

	filter "configurations:Debug"
		defines
		{
			"MEDUZA_DEBUG"
		}
		targetname "Meduza_d"
		symbols "On"
		editandcontinue  "On"	

	filter "configurations:Release"
		defines
		{
			"MEDUZA_RELEASE"
		}
		optimize "On"
		targetname "Meduza"
		
	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"
		characterset  "MBCS"
		excludes { "**/Linux/**" }	
		
		defines
		{
			"PLATFORM_WINDOWS",
			"GLEW_STATIC"
		}
		
	filter {"platforms:x64", "configurations:Release"}
		buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"	
	
	warnings "Extra"
	flags { "FatalWarnings" }
	
	links
	{
		"Meduza"
	}
	
	targetdir ("Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputDir .. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "%{prj.name}/Source/pch.cpp"
	
	files
	{
		"%{prj.name}/Include/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{
		"$(SolutionDir)%{prj.name}/Include",
		"$(SolutionDir)Meduza/Include/Core",
		"$(SolutionDir)Meduza/External",
		"$(SolutionDir)%{prj.name}/External/Optick/Include"
	}

	filter {"files:**/main.cpp"}
		flags { "NoPCH" }		

	filter "configurations:Debug"
		symbols "On"
		editandcontinue  "On"	
		defines
		{
			"MEDUZA_DEBUG"
		}		

	filter "configurations:Release"
		defines
		{
			"MEDUZA_RELEASE"
		}
		optimize "On"
		
			
	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"
		excludes { "**/Linux/**" }	

		defines
		{
			"PLATFORM_WINDOWS",
			"GLEW_STATIC"
		}
		
	filter {"platforms:windows", "configurations:Release"}
		buildoptions "/MT"
		
	filter {"platforms:x64"}	
		libdirs { "OptickCore.lib", "$(SolutionDir)Sandbox/External/Optick/lib/$(Platform)/%{cfg.buildcfg}" }
		postbuildcommands
		{
			("{COPY} $(SolutionDir)Sandbox/External/Optick/lib/x64/%{cfg.buildcfg}/OptickCore.dll $(outDir)")
		}
		
		links
		{
			"OptickCore.lib"
		}
		
		