cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})

# Specify the source files
add_executable(${PROJECT_NAME} src/main.cpp)

# GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add GLFW as a subdirectory
add_subdirectory(external/glfw)

# Include GLFW headers
target_include_directories(${PROJECT_NAME} PRIVATE external/glfw/include)

# Link GLFW to the project
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
