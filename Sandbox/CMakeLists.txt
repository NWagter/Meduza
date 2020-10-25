cmake_minimum_required(VERSION 3.16.3)

project(Sandbox)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(Sandbox 
    Source/main.cpp Source/Application.cpp 
)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set_target_properties(Sandbox
PROPERTIES 
RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(Sandbox PUBLIC 
    ${PROJECT_SOURCE_DIR}/Include 
)

target_link_libraries( Sandbox
        Meduza
)

if(WIN32)
	add_compile_definitions(PLATFORM_WINDOWS)
	target_link_libraries( Sandbox
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
    target_link_libraries( Sandbox
        X11
        ${OPENGL_LIBRARY}
        ${CMAKE_DL_LIBS}
    )
elseif(APPLE)
	add_compile_definitions(PLATFORM_APPLE)
endif()

file(COPY ${PROJECT_SOURCE_DIR}/Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS Sandbox)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/Assets DESTINATION bin)