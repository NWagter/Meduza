workspace "Meduza"

	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Developer",
		"Release"
	}
	platforms { "ARM", "x64"}
	
	filter "platforms:x64*"
		architecture "x64"
		system "windows"

	filter "platforms:ARM"
		architecture "ARM"
		system "linux"
		
	
outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

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

	filter "configurations:Debug"
		defines
		{
			"DEV",
			"Meduza_Debug"
		}
		targetname "Meduza_d"
		symbols "On"

	filter "configurations:Developer"
		defines
		{
			"DEV",
			"Meduza_Developer"
		}
		targetname "Meduza_dev"
		optimize "On"

	filter "configurations:Release"
		defines
		{
			"Meduza_Release"
		}
		optimize "On"
		buildoptions "/MT"
		targetname "Meduza"
		
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
		
	filter "system:linux"
		cppdialect "C++14"
		characterset  "MBCS"
		excludes { "**/Windows/**" }
		defines
		{
			"PLATFORM_LINUX"
		}
		

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"	
	
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
		"$(SolutionDir)Meduza/External/Optick/Include"
	}
	
	links
	{
		"Meduza"
	}

	filter {"files:**/main.cpp"}
		flags { "NoPCH" }		

	filter "configurations:Debug"
		symbols "On"	
		defines
		{
			"DEV"
		}

	filter "configurations:Developer"
		optimize "On"			
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
		
			
	filter "system:windows"
		cppdialect "C++14"
		staticruntime "On"
		systemversion "10.0.18362.0"

		defines
		{
			"PLATFORM_WINDOWS",
			"GLEW_STATIC"
		}
		
	filter {"platforms:x64", "configurations:Debug"}	
		libdirs { "OptickCore.lib", "$(SolutionDir)Meduza/External/Optick/lib/$(Platform)/Debug" }
		postbuildcommands
		{
			("{COPY} $(SolutionDir)/Meduza/External/Optick/lib/x64/Debug/OptickCore.dll $(outDir)")
		}
		
		links
		{
			"OptickCore.lib"
		}
	
	filter {"platforms:x64", "configurations:Developer"}	
		libdirs { "OptickCore.lib", "$(SolutionDir)Meduza/External/Optick/lib/$(Platform)/Release" }
		postbuildcommands
		{
			("{COPY} $(SolutionDir)/Meduza/External/Optick/lib/x64/Release/OptickCore.dll $(outDir)")
		}
		
		links
		{
			"OptickCore.lib"
		}

	filter "system:linux"
		cppdialect "C++14"
		characterset  "MBCS"
		clr "On"
		removefiles { "**/Windows/**" }
		warnings "Off"
		targetextension ".out"
		defines
		{
			"PLATFORM_LINUX"
		}
		includedirs { "/usr/include", "/usr/local/include", "/opt/include" }
		
		