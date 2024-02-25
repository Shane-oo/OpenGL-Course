//
// Created by Shane Monck on 29/12/2023.
//

#include "Light.h"


Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambientIntensity = 1.0f;

    diffuseIntensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity) {
    colour = glm::vec3(red, green, blue);
    this->ambientIntensity = ambientIntensity;

    this->diffuseIntensity = diffuseIntensity;
}

void Light::UseLight(GLint ambientIntensityLocation,
                     GLint ambientColourLocation,
                     GLint diffuseIntensityLocation) {
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);

    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}


