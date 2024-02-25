//
// Created by Shane Monck on 31/12/2023.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() : Light() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
                                   GLfloat ambient_intensity, GLfloat diffuse_intensity,
                                   GLfloat x_direction, GLfloat y_direction, GLfloat z_direction) : Light(red,
                                                                                                          green,
                                                                                                          blue,
                                                                                                          ambient_intensity,
                                                                                                          diffuse_intensity) {
    direction = glm::vec3(x_direction, y_direction, z_direction);
}

void DirectionalLight::UseDirectionalLight(GLint ambient_intensity_location, GLint ambient_colour_location,
                                           GLint diffuse_intensity_location, GLint direction_location) {
    glUniform3f(direction_location, direction.x, direction.y, direction.z);

    UseLight(ambient_intensity_location, ambient_colour_location, diffuse_intensity_location);
}
