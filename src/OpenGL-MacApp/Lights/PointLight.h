//
// Created by Shane Monck on 31/12/2023.
//

#ifndef OPENGL_MACAPP_POINTLIGHT_H
#define OPENGL_MACAPP_POINTLIGHT_H


#include "Light.h"

class PointLight : public Light {
protected:
    glm::vec3 position;

    GLfloat constant;
    GLfloat linear;
    GLfloat exponent;

public:
    PointLight();

    PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
               GLfloat xPosition, GLfloat yPosition, GLfloat zPosition,
               GLfloat constant, GLfloat linear, GLfloat exponent);


    ~PointLight();

    void UsePointLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
                       GLint diffuseIntensityLocation, GLint positionLocation,
                       GLint constantLocation, GLint linearLocation, GLint exponentLocation);
};


#endif //OPENGL_MACAPP_POINTLIGHT_H
