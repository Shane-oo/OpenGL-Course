//
// Created by Shane Monck on 29/12/2023.
//

#include "Light.h"


Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambient_intensity = 1.0f;

    diffuse_intensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity, GLfloat diffuse_intensity) {
    colour = glm::vec3(red, green, blue);
    this->ambient_intensity = ambient_intensity;

    this->diffuse_intensity = diffuse_intensity;
}

void Light::UseLight(GLint ambient_intensity_location,
                     GLint ambient_colour_location,
                     GLint diffuse_intensity_location) {
    glUniform3f(ambient_colour_location, colour.x, colour.y, colour.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);

    glUniform1f(diffuse_intensity_location, diffuse_intensity);
}


