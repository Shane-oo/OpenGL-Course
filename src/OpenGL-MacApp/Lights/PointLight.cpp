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

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity, GLfloat diffuse_intensity,
                       GLfloat x_position, GLfloat y_position, GLfloat z_position, GLfloat constant, GLfloat linear,
                       GLfloat exponent) : Light(red, green, blue, ambient_intensity, diffuse_intensity) {
    position = glm::vec3(x_position, y_position, z_position);
    this->constant = constant;
    this->linear = linear;
    this->exponent = exponent;
}


PointLight::~PointLight() {

}

void PointLight::UsePointLight(GLint ambient_intensity_location, GLint ambient_colour_location,
                               GLint diffuse_intensity_location, GLint position_location,
                               GLint constant_location, GLint linear_location, GLint exponent_location) {
    glUniform3f(position_location, position.x, position.y, position.z);
    glUniform1f(constant_location, constant);
    glUniform1f(linear_location, linear);
    glUniform1f(exponent_location, exponent);

    UseLight(ambient_intensity_location, ambient_colour_location, diffuse_intensity_location);
}

