cmake_minimum_required(VERSION 3.27)
project(OpenGL_MacApp)


# Set C++ standard
set(CMAKE_CXX_STANDARD 20)


# Find GLFW package
find_package(glfw3 REQUIRED)

# Find GLEW package
# https://stackoverflow.com/questions/27472813/linking-glew-with-cmake
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Find GLM package
find_package(glm REQUIRED)

# Add your source files
add_executable(OpenGL_MacApp
        main.cpp
        Mesh.cpp
        Mesh.h
        Shader.cpp
        Shader.h
        GLWindow.cpp
        GLWindow.h
        Camera.cpp
        Camera.h
        Texture.cpp
        Texture.h
        Light.cpp
        Light.h)

# Copy the Resources folder to the build and binary directory
add_custom_target(
        copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${PROJECT_SOURCE_DIR}/Resources
        ${PROJECT_BINARY_DIR}/Resources
        COMMENT "Copying Resources into binary directory")

add_dependencies(OpenGL_MacApp copy_resources)


# Link GLFW Library
target_link_libraries(OpenGL_MacApp PRIVATE glfw)

# Link GLEW Library
target_link_libraries(OpenGL_MacApp PRIVATE GLEW::GLEW)

# Link OpenGL Library
target_link_libraries(OpenGL_MacApp PRIVATE ${OPENGL_gl_LIBRARY})

# Link GLM Library
target_link_directories(OpenGL_MacApp PRIVATE glm)

