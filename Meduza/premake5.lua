workspace "Meduza"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Developer",
		"Release"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Meduza"
	location "Meduza"
	kind "StaticLib"
	language "C++"

	targetdir ("Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputDir .. "/%{prj.name}")

	pchheader "mePch.h"
	pchsource "%{prj.name}/Source/mePch.cpp"

	files
	{
		"%{prj.name}/Include/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/External/Glad/**.c"
	}

	includedirs
	{
		"$(SolutionDir)%{prj.name}/Include",
		"$(SolutionDir)%{prj.name}/Include/Core",
		"$(SolutionDir)%{prj.name}/External",
		"$(SolutionDir)%{prj.name}/External/Dx12",
		"$(SolutionDir)%{prj.name}/External/Optick/Include",
		"$(SolutionDir)%{prj.name}/External/Glad/include"
	}
	
	filter {"files:**.c"}
		flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"
		characterset  "MBCS"

	defines
	{
		"PLATFORM_WINDOWS",
		"GLEW_STATIC"
	}

	filter "configurations:Debug"
		defines
		{
			"DEV",
			"Meduza_Debug"
		}

		symbols "On"

	filter "configurations:Developer"
		defines
		{
			"DEV",
			"Meduza_Developer"
		}
		optimize "On"

	filter "configurations:Release"
		defines
		{
			"Meduza_Release"
		}
		optimize "On"
		buildoptions "/MT"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("Executable/" .. outputDir .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputDir .. "/%{prj.name}")

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
		"$(SolutionDir)Meduza/External/Optick/Include"
	}

	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"

	defines
	{
		"PLATFORM_WINDOWS"
	}

	links
	{
		"Meduza"
	}


	filter "configurations:Debug"
		symbols "On"	

		libdirs { "$(SolutionDir)Meduza/External/Optick/lib/$(Platform)/Debug" }

		postbuildcommands
		{
			("{COPY} $(SolutionDir)/Meduza/External/Optick/lib/x64/Debug/OptickCore.dll $(outDir)")
		}

	filter "configurations:Developer"

		optimize "On"		
		
		libdirs { "OptickCore.lib", "$(SolutionDir)Meduza/External/Optick/lib/$(Platform)/Release" }
		postbuildcommands
		{
			("{COPY} $(SolutionDir)/Meduza/External/Optick/lib/x64/Release/OptickCore.dll $(outDir)")
		}

	filter  { "configurations:Debug", "configurations:Developer"}

		links
		{
			"OptickCore.lib"
		}
		defines
		{
			"DEV"
		}

	filter "configurations:Release"
		defines
		{
			"Meduza_Release"
		}
		optimize "On"
		buildoptions "/MT"