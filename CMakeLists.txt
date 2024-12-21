cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

set(PROJECT_NAME BattleCity)

project(${PROJECT_NAME})

# GLFW options
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add GLFW and GLAD as subdirectories
add_subdirectory(external/glfw)
add_subdirectory(external/glad)

# Specify the source files
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/Renderer/ShaderProgram.cpp
    src/Renderer/ShaderProgram.h
    src/Renderer/Texture2D.cpp
    src/Renderer/Texture2D.h
    src/Renderer/Sprite.cpp
    src/Renderer/Sprite.h
    src/Resources/ResourceManager.cpp
    src/Resources/ResourceManager.h
    src/Resources/stb_image.h
)

# Set C++ standard
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

# Include directories
target_include_directories(${PROJECT_NAME}
    PUBLIC
        external/glfw/include
        external/glad/include
        external/glm
)

# Link libraries
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw
        glad
)

# Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Copy resources
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/res $<TARGET_FILE_DIR:${PROJECT_NAME}>/res
)
