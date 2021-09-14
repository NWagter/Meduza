cmake_minimum_required(VERSION 3.16.3)

project(LuaLib)

# The recommended way to collect sources in variable by explicitly specifying the source files
file(GLOB SOURCE src/*.c)

  
add_library(${PROJECT_NAME}
${SOURCE})

target_include_directories (${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")