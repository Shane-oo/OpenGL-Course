//
// Created by Shane Monck on 31/12/2023.
//

#include "PointLight.h"

PointLight::PointLight() : Light() {
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    constant = 1.0f;
    linear = 0.0f;
    exponent = 0.0f;
    // L/ax^2 + bx + c
    // L/0 + 0 + 1
}

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
                       GLfloat xPosition, GLfloat yPosition, GLfloat zPosition, GLfloat constant, GLfloat linear,
                       GLfloat exponent) : Light(red, green, blue, ambientIntensity, diffuseIntensity) {
    position = glm::vec3(xPosition, yPosition, zPosition);
    this->constant = constant;
    this->linear = linear;
    this->exponent = exponent;
}


PointLight::~PointLight() {

}

void PointLight::UsePointLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
                               GLint diffuseIntensityLocation, GLint positionLocation,
                               GLint constantLocation, GLint linearLocation, GLint exponentLocation) {
    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);

    UseLight(ambientIntensityLocation, ambientColourLocation, diffuseIntensityLocation);
}

