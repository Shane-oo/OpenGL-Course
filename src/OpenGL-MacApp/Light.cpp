//
// Created by Shane Monck on 29/12/2023.
//

#include <cstdio>
#include "Light.h"

Light::Light() {
    colour = glm::vec3(1.0f, 1.0f, 1.0f);
    ambient_intensity = 1.0f;

    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    diffuse_intensity = 0.0f;
}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambient_intensity,
             GLfloat x_direction, GLfloat y_direction, GLfloat z_direction, GLfloat diffuse_intensity) {
    colour = glm::vec3(red, green, blue);
    this->ambient_intensity = ambient_intensity;

    direction = glm::vec3(x_direction, y_direction, z_direction);
    this->diffuse_intensity = diffuse_intensity;
}


void Light::UseLight(int ambient_intensity_location, int ambient_colour_location,
                     int diffuse_intensity_location, int direction_location) {
    glUniform3f(ambient_colour_location, colour.x, colour.y, colour.z);
    glUniform1f(ambient_intensity_location, ambient_intensity);
//    printf("ambient_colour_location %d and the value x: %f y: %f z:%f \n", ambient_colour_location, colour.x, colour.y,
//           colour.z);
//    printf("ambient_intensity_location %d and the value %f\n", ambient_intensity_location, ambient_intensity);


    glUniform3f(direction_location, direction.x, direction.y, direction.z);
    glUniform1f(diffuse_intensity_location, diffuse_intensity);

//    printf("Direction_location %d and the value x: %f y: %f z:%f \n", direction_location, direction.x, direction.y,
//           direction.z);
//
//    printf("diffuse_intensity_location %d and the value %f\n", diffuse_intensity_location, diffuse_intensity);
}

