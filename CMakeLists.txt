cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

# Specify the source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Renderer/ShaderProgram.cpp
    src/Renderer/ShaderProgram.h
    src/Resources/ResourceManager.cpp
    src/Resources/ResourceManager.h
)

# GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add GLFW as a subdirectory
add_subdirectory(external/glfw)

# Include GLFW headers
target_include_directories(${PROJECT_NAME} PUBLIC external/glfw/include)

# Link GLFW to the project
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)

# Add GLAD as a subdirectory
add_subdirectory(external/glad)

# Include GLAD headers
target_include_directories(${PROJECT_NAME} PUBLIC external/glad/include)

# Link GLAD to the project
target_link_libraries(${PROJECT_NAME} PRIVATE glad)

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                   ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res)
