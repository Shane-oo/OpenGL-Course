//
// Created by Shane Monck on 29/12/2023.
//

#ifndef OPENGL_MACAPP_LIGHT_H
#define OPENGL_MACAPP_LIGHT_H


#include <glm/vec3.hpp>
#include <GL/glew.h>

class Light {
private:
    glm::vec3 colour;
    GLfloat ambient_intensity;
public:
    Light();

    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity);

    void UseLight(int ambient_intensity_location, int ambient_colour_location);
};


#endif //OPENGL_MACAPP_LIGHT_H
