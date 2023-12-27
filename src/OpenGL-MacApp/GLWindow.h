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
    double mouse_last_x;
    double mouse_last_y;
    double mouse_x_change;
    double mouse_y_change;
    bool mouse_first_moved;

    void CreateCallbacks();

    static void HandleKeys(GLFWwindow *window, int key, int code, int action, int mode);

    static void HandleMouse(GLFWwindow *window, double x_position, double y_position);

    static void SetMousePositions(GLWindow *the_window, double x, double y);

public:
    GLWindow();

    GLWindow(GLint window_width, GLint window_height);

    ~GLWindow();

    GLfloat GetBufferWidth() const;

    GLfloat GetBufferHeight() const;

    bool GetShouldClose();

    bool *GetKeys();

    GLfloat GetMouseXChange();

    GLfloat GetMouseYChange();

    int Initialise();

    void SwapBuffers();
};


#endif //OPENGL_MACAPP_GLWINDOW_H
