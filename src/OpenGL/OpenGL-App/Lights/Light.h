//
// Created by Shane Monck on 29/12/2023.
//

#ifndef OPENGL_MACAPP_LIGHT_H
#define OPENGL_MACAPP_LIGHT_H


#include <glm/vec3.hpp>
#include <GL/glew.h>
#include <optional>

class Light {
protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;

    GLfloat diffuseIntensity;

    void UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
                  GLint diffuseIntensityLocation);

public:
    Light();

    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity);

};


#endif //OPENGL_MACAPP_LIGHT_H
