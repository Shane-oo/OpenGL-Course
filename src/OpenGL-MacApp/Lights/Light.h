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
    GLfloat ambient_intensity;

    GLfloat diffuse_intensity;

    void UseLight(GLint ambient_intensity_location, GLint ambient_colour_location,
                  GLint diffuse_intensity_location);

public:
    Light();

    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity, GLfloat diffuse_intensity);

};


#endif //OPENGL_MACAPP_LIGHT_H
