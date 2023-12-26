//
// Created by Shane Monck on 26/12/2023.
//

#ifndef OPENGL_MACAPP_CAMERA_H
#define OPENGL_MACAPP_CAMERA_H

#include <glm/vec3.hpp>
#include <glm/fwd.hpp>

class Camera {
private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    GLfloat yaw;
    GLfloat pitch;
    GLfloat roll;

    GLfloat movement_speed;
    GLfloat turn_speed;

    void Update();

public:
    Camera();
    Camera(glm::vec3 start_position, glm::vec3 start_up, GLfloat start_yaw, GLfloat start_pitch,
           GLfloat start_movement_speed, GLfloat start_turn_speed);

    ~Camera();

    void KeyControl(const bool *keys, double delta_time);

    glm::mat4 CalculateViewMatrix();
};


#endif //OPENGL_MACAPP_CAMERA_H
