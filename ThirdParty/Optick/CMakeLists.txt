cmake_minimum_required(VERSION 3.16.3)

project(Optick)

# The recommended way to collect sources in variable by explicitly specifying the source files
file(GLOB SOURCE Source/*.cpp)

  
add_library(${PROJECT_NAME}
${SOURCE})

target_include_directories (${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/Source")