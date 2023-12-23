//
// Created by Shane Monck on 23/12/2023.
//

#ifndef OPENGL_MACAPP_GLWINDOW_H
#define OPENGL_MACAPP_GLWINDOW_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow {
private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

public:
    GLWindow();

    GLWindow(GLint windowWidth, GLint windowHeight);

    ~GLWindow();

    int Initialise();

    GLfloat GetBufferWidth() const;

    GLfloat GetBufferHeight() const;

    bool GetShouldClose();

    void SwapBuffers();
};


#endif //OPENGL_MACAPP_GLWINDOW_H
