//
// Created by Shane Monck on 31/12/2023.
//

#ifndef OPENGL_MACAPP_POINTLIGHT_H
#define OPENGL_MACAPP_POINTLIGHT_H


#include "Light.h"

class PointLight : public Light {
private:
    glm::vec3 position;

    GLfloat constant;
    GLfloat linear;
    GLfloat exponent;

public:
    PointLight();

    PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity, GLfloat diffuse_intensity,
               GLfloat x_position, GLfloat y_position, GLfloat z_position,
               GLfloat constant, GLfloat linear, GLfloat exponent);


    ~PointLight();

    void UsePointLight(GLint ambient_intensity_location, GLint ambient_colour_location,
                       GLint diffuse_intensity_location, GLint position_location,
                       GLint constant_location, GLint linear_location, GLint exponent_location);
};


#endif //OPENGL_MACAPP_POINTLIGHT_H
