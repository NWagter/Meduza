cmake_minimum_required(VERSION 3.16.3)

project(Sandbox)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file(GLOB GAME_SOURCE
    Source/Games/*.cpp
    Source/Games/Example/*.cpp
    Source/Components/*.cpp
    Source/Systems/*.cpp

    
    Source/Games/Chess/*.cpp
    Source/Components/Chess/*.cpp
    Source/Systems/Chess/*.cpp

    
    Source/Games/Physics2D/*.cpp
    Source/Components/Physics2D/*.cpp
    Source/Systems/Physics2D/*.cpp
)

add_executable(${PROJECT_NAME} 
    Source/Sandbox.cpp 
	${GAME_SOURCE}
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(${PROJECT_NAME}
PROPERTIES 
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/Include 
)

target_link_libraries( ${PROJECT_NAME}
        Meduza
)

if(WIN32)
	add_compile_definitions(PLATFORM_WINDOWS)
	target_link_libraries( ${PROJECT_NAME}
    d3d12.lib
    dxgi.lib
    dxguid.lib
    d3dcompiler.lib
    Shlwapi.lib
	)
elseif(UNIX AND NOT APPLE)
    find_package(OpenGL)
    add_compile_definitions(PLATFORM_LINUX)
    include_directories(/usr/include/X11)
    target_link_libraries( ${PROJECT_NAME}
        X11
        ${OPENGL_LIBRARY}
        ${CMAKE_DL_LIBS}
    )
elseif(APPLE)
	add_compile_definitions(PLATFORM_APPLE)
endif()

file(COPY ${PROJECT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ${PROJECT_NAME})
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Assets DESTINATION bin)