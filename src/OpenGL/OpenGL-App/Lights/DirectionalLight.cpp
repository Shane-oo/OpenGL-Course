//
// Created by Shane Monck on 31/12/2023.
//

#include "DirectionalLight.h"
#include <glm/gtc/matrix_transform.hpp>

DirectionalLight::DirectionalLight() : Light() {
  direction = glm::vec3(0.0f, -1.0f, 0.0f);
  lightProj = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, 0.1f, 100.0f);
}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
                                   GLfloat ambient_intensity,
                                   GLfloat diffuse_intensity,
                                   GLfloat x_direction, GLfloat y_direction,
                                   GLfloat z_direction, GLsizei shadowWidth,
                                   GLsizei shadowHeight)
    : Light(red, green, blue, ambient_intensity, diffuse_intensity, shadowWidth,
            shadowHeight) {
  direction = glm::vec3(x_direction, y_direction, z_direction);
  lightProj = glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, 0.1f, 20.0f);
}

void DirectionalLight::UseDirectionalLight(GLint ambient_intensity_location,
                                           GLint ambient_colour_location,
                                           GLint diffuse_intensity_location,
                                           GLint direction_location) {
  glUniform3f(direction_location, direction.x, direction.y, direction.z);

  UseLight(ambient_intensity_location, ambient_colour_location,
           diffuse_intensity_location);
}
glm::mat4 DirectionalLight::CalculateLightTransform() {
  return lightProj * glm::lookAt(-direction, 
                                 glm::vec3(0.0f, 0.0f, 0.0f),
                                 glm::vec3(0.0f, 1.0f, 0.0f));
}
