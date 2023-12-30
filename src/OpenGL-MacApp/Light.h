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

    glm::vec3 direction;
    GLfloat diffuse_intensity;
public:
    Light();

    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity,
          GLfloat x_direction, GLfloat y_direction, GLfloat z_direction, GLfloat diffuse_intensity);

    void UseLight(int ambient_intensity_location, int ambient_colour_location,
                  int diffuse_intensity_location, int direction_location);
};


#endif //OPENGL_MACAPP_LIGHT_H
