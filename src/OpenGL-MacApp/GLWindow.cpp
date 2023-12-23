//
// Created by Shane Monck on 23/12/2023.
//

#include <cstdio>
#include "GLWindow.h"

GLWindow::GLWindow() {
    width = 800;
    height = 600;
}

GLWindow::GLWindow(GLint windowWidth, GLint windowHeight) {
    width = windowWidth;
    height = windowHeight;
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}

int GLWindow::Initialise() {
    // Initialise GLFW
    if (glfwInit() == GLFW_FALSE) {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }

    // Setup GLFW window properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // don't use deprecated features, no backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    mainWindow = glfwCreateWindow(width, height, "Test Window", nullptr, nullptr);
    if (!mainWindow) {
        printf("GLFW window creation failed");
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    // Set context for GLEW to use
    glfwMakeContextCurrent(mainWindow);

    // Initialise GLEW
    // Allow modern extension features
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW initialisation failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    // tell OpenGL to draw triangles over others
    glEnable(GL_DEPTH_TEST);

    // Create Viewport
    glViewport(0, 0, bufferWidth, bufferHeight);
}


GLfloat GLWindow::GetBufferWidth() const {
    return (GLfloat) bufferWidth;
}

GLfloat GLWindow::GetBufferHeight() const {
    return (GLfloat) bufferHeight;
}

bool GLWindow::GetShouldClose() {
    return glfwWindowShouldClose(mainWindow);
}

void GLWindow::SwapBuffers() {
    glfwSwapBuffers(mainWindow);
}


