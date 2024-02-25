//
// Created by Shane Monck on 31/12/2023.
//

#ifndef OPENGL_MACAPP_DIRECTIONALLIGHT_H
#define OPENGL_MACAPP_DIRECTIONALLIGHT_H


#include "Light.h"

class DirectionalLight : public Light {
private:
    glm::vec3 direction;

public:
    DirectionalLight();

    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity, GLfloat diffuse_intensity,
                     GLfloat x_direction, GLfloat y_direction, GLfloat z_direction);

    void UseDirectionalLight(GLint ambient_intensity_location, GLint ambient_colour_location,
                             GLint diffuse_intensity_location, GLint direction_location);
};


#endif //OPENGL_MACAPP_DIRECTIONALLIGHT_H
