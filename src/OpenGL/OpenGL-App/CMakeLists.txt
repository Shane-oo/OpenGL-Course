# CMakeList.txt : CMake project for OpenGL-App, include source and define
# project specific logic here.
#


# Copy the Resources folder to the build and binary directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/Resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


# Add source to this project's executable.
add_executable (OpenGL-App    
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
        Lights/Light.cpp
        Lights/Light.h
        Material.cpp
        Material.h
        Lights/DirectionalLight.cpp
        Lights/DirectionalLight.h
        Lights/PointLight.cpp
        Lights/PointLight.h
        CommonValues.h
        Lights/SpotLight.cpp
        Lights/SpotLight.h
        Model.cpp
        Model.h)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGL-App PROPERTY CXX_STANDARD 20)
endif()

# Find GLFW package
find_package(glfw3 REQUIRED)

# Find GLEW package
# https://stackoverflow.com/questions/27472813/linking-glew-with-cmake
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})

# Find GLM package
find_package(glm REQUIRED)

# Find assimp package
find_package(assimp CONFIG REQUIRED)




# Link GLFW Library
target_link_libraries(OpenGL-App PRIVATE glfw)

# Link GLEW Library
target_link_libraries(OpenGL-App PRIVATE GLEW::GLEW)

# Link OpenGL Library
target_link_libraries(OpenGL-App PRIVATE ${OPENGL_gl_LIBRARY})

# Link GLM Library
target_link_directories(OpenGL-App PRIVATE glm)

# Link assimp Library
target_link_libraries(OpenGL-App PRIVATE assimp::assimp)