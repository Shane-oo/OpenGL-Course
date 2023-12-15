cmake_minimum_required(VERSION 3.27)
project(OpenGL_MacApp)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)

# Find GLFW package
find_package(glfw3 REQUIRED)

# Find GLEW package
find_package(GLEW REQUIRED)

# Add your source files
add_executable(OpenGL_MacApp main.cpp)

# Link GLFW Library
target_link_libraries(OpenGL_MacApp PRIVATE glfw)

# Link GLEW Library
target_link_libraries(OpenGL_MacApp PRIVATE GLEW)
