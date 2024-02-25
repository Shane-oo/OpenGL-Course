//
// Created by Shane Monck on 23/12/2023.
//

#include <cstdio>
#include "GLWindow.h"

GLWindow::GLWindow() {
    width = 800;
    height = 600;

    for (bool &key: keys) {
        key = false;
    }
    mouse_x_change = 0.0f;
    mouse_y_change = 0.0f;

    mouse_first_moved = false;
}

GLWindow::GLWindow(GLint window_width, GLint window_height) {
    width = window_width;
    height = window_height;
    for (bool &key: keys) {
        key = false;
    }
    mouse_x_change = 0.0f;
    mouse_y_change = 0.0f;

    mouse_first_moved = false;
}

GLWindow::~GLWindow() {
    glfwDestroyWindow(main_window);
    glfwTerminate();
}

GLfloat GLWindow::GetBufferWidth() const {
    return (GLfloat) buffer_width;
}

GLfloat GLWindow::GetBufferHeight() const {
    return (GLfloat) buffer_height;
}

bool GLWindow::GetShouldClose() {
    return glfwWindowShouldClose(main_window);
}

bool *GLWindow::GetKeys() {
    return keys;
}

GLfloat GLWindow::GetMouseXChange() {
    double change = mouse_x_change;
    mouse_x_change = 0.0f; // reset
    return (GLfloat) change;
}

GLfloat GLWindow::GetMouseYChange() {
    double change = mouse_y_change;
    mouse_y_change = 0.0f; // reset
    return (GLfloat) change;
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

    main_window = glfwCreateWindow(width, height, "Test Window", nullptr, nullptr);
    if (!main_window) {
        printf("GLFW window creation failed");
        glfwTerminate();
        return 1;
    }

    // Get Buffer size information
    glfwGetFramebufferSize(main_window, &buffer_width, &buffer_height);

    // Set context for GLEW to use
    glfwMakeContextCurrent(main_window);

    // Handle Key + Mouse Input
    CreateCallbacks();
    // Lock Cursor to window
    glfwSetInputMode(main_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Initialise GLEW
    // Allow modern extension features
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        printf("GLEW initialisation failed");
        glfwDestroyWindow(main_window);
        glfwTerminate();
        return 1;
    }

    // tell OpenGL to draw triangles over others
    glEnable(GL_DEPTH_TEST);

    // Create Viewport
    glViewport(0, 0, buffer_width, buffer_height);

    glfwSetWindowUserPointer(main_window, this);

    return 0;
}


void GLWindow::SwapBuffers() {
    glfwSwapBuffers(main_window);
}

void GLWindow::CreateCallbacks() {
    glfwSetKeyCallback(main_window, HandleKeys);
    glfwSetCursorPosCallback(main_window, HandleMouse);
}

// Keyboard callback
void GLWindow::HandleKeys(GLFWwindow *window, int key, int code, int action, int mode) {
    auto *the_window = static_cast<GLWindow *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024) {
        if (action == GLFW_PRESS) {
            the_window->keys[key] = true;
        } else if (action == GLFW_RELEASE) {
            the_window->keys[key] = false;
        }
    }
}

void GLWindow::HandleMouse(GLFWwindow *window, double x_position, double y_position) {
    auto *the_window = static_cast<GLWindow *>(glfwGetWindowUserPointer(window));

    if (!the_window->mouse_first_moved) {
        SetMousePositions(the_window, x_position, y_position);
        the_window->mouse_first_moved = true;
    }

    the_window->mouse_x_change = x_position - the_window->mouse_last_x;
    the_window->mouse_y_change = the_window->mouse_last_y - y_position; // not inverted

    SetMousePositions(the_window, x_position, y_position);
}

void GLWindow::SetMousePositions(GLWindow *the_window, double x, double y) {
    the_window->mouse_last_x = x;
    the_window->mouse_last_y = y;
}




