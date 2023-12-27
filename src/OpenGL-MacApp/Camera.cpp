//
// Created by Shane Monck on 26/12/2023.
//


#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_transform.hpp>
#include "Camera.h"

Camera::Camera() {

}

Camera::Camera(glm::vec3 start_position, glm::vec3 start_up, GLfloat start_yaw, GLfloat start_pitch,
               GLfloat start_movement_speed, GLfloat start_turn_speed) {
    position = start_position;
    world_up = start_up;
    yaw = start_yaw;
    pitch = start_pitch;
    front = glm::vec3(0.0f, 0.0f, -1.0f);

    movement_speed = start_movement_speed;
    turn_speed = start_turn_speed;

    Update();
}

Camera::~Camera() {

}

void Camera::Update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));

}

void Camera::KeyControl(const bool *keys, double delta_time) {
    auto velocity = static_cast<GLfloat>(movement_speed * delta_time);

    if (keys[GLFW_KEY_W]) {
        position += front * velocity;
    }
    if (keys[GLFW_KEY_S]) {
        position -= front * velocity;
    }
    if (keys[GLFW_KEY_A]) {
        position -= right * velocity;
    }
    if (keys[GLFW_KEY_D]) {
        position += right * velocity;
    }
}

glm::mat4 Camera::CalculateViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::MouseControl(GLfloat x_change, GLfloat y_change) {
    x_change *= turn_speed;
    y_change *= turn_speed;

    yaw += x_change;
    pitch += y_change;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }

    if (pitch < -89.0f) {
        pitch = -89.0f;
    }

    Update();
}

