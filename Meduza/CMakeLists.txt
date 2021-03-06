cmake_minimum_required(VERSION 3.16.3)

project (Meduza)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
	add_compile_definitions(PLATFORM_WINDOWS)
	file(GLOB PLATFORM_SOURCE Source/Platform/Windows/*.cpp
	Source/Platform/Windows/Graphics/*.cpp
	Source/Platform/Windows/Editor/*.cpp
	Source/Platform/Windows/Resources/*.cpp	
	Source/Platform/Windows/Helper/*.cpp
	${PROJECT_SOURCE_DIR}/External/Win/DX12/src/*.cpp	
	${PROJECT_SOURCE_DIR}/External/Win/imgui/*.cpp)	
	file(GLOB EXTERNAL_INCLUDE ${PROJECT_SOURCE_DIR}/External/Win/DX12/Include
	${PROJECT_SOURCE_DIR}/External/Win/imgui)
elseif(UNIX AND NOT APPLE)
	add_compile_definitions(PLATFORM_LINUX)
	file(GLOB PLATFORM_SOURCE Source/Platform/Linux/*.cpp
	Source/Platform/Linux/Graphics/*.cpp
	Source/Platform/Linux/Resources/*.cpp	
	Source/Platform/Linux/Helper/*.cpp
	${PROJECT_SOURCE_DIR}/External/Linux/src/*.c)
	file(GLOB EXTERNAL_INCLUDE ${PROJECT_SOURCE_DIR}/External/Linux/Include)
elseif(APPLE)
	add_compile_definitions(PLATFORM_APPLE)
	file(GLOB PLATFORM_SOURCE Source/Platform/MacOS/*.cpp)
	file(GLOB EXTERNAL_INCLUDE ${PROJECT_SOURCE_DIR}/External/MacOS)
endif()

file(GLOB PLATFORM_GENERAL_SOURCE
	${PROJECT_SOURCE_DIR}/External/General/imgui/*.cpp
	Source/Core/*.cpp
	Source/Math/*.cpp

	Source/Physics/*.cpp
	Source/Physics/Systems/*.cpp

	Source/ECS/*.cpp
	Source/Core/Systems/*.cpp
	Source/Core/Components/*.cpp
	
	Source/Utils/*.cpp
	Source/Platform/General/*.cpp
	Source/Platform/General/Editor/*.cpp
	Source/Platform/General/Graphics/*.cpp
	Source/Platform/General/Graphics/*.cpp
	Source/Platform/General/Resources/*.cpp
	Source/Platform/General/Events/*.cpp
	Source/Platform/General/Events/Input/*.cpp
	Source/Platform/General/FileSystem/*.cpp
)

file(GLOB EXTERNAL_GENERAL ${PROJECT_SOURCE_DIR}/External/General/Include
${PROJECT_SOURCE_DIR}/External/General/imgui)

add_library(${PROJECT_NAME} 
	${SOURCES}
	${PLATFORM_GENERAL_SOURCE} 
	${PLATFORM_SOURCE}
	)

target_include_directories(Meduza PUBLIC 
		${PROJECT_SOURCE_DIR}/Include
		${EXTERNAL_INCLUDE}
		${EXTERNAL_GENERAL}
)
