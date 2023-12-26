//
// Created by Shane Monck on 23/12/2023.
//

#ifndef OPENGL_MACAPP_GLWINDOW_H
#define OPENGL_MACAPP_GLWINDOW_H


#include <GL/glew.h>
#include <GLFW/glfw3.h>

class GLWindow {
private:
    GLFWwindow *main_window;
    GLint width, height;
    GLint buffer_width, buffer_height;

    bool keys[1024];

    void CreateCallbacks();

    static void HandleKeys(GLFWwindow *window, int key, int code, int action, int mode);

public:
    GLWindow();

    GLWindow(GLint window_width, GLint window_height);

    ~GLWindow();

    int Initialise();

    GLfloat GetBufferWidth() const;

    GLfloat GetBufferHeight() const;

    bool GetShouldClose();

    void SwapBuffers();
};


#endif //OPENGL_MACAPP_GLWINDOW_H
