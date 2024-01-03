//
// Created by Shane Monck on 3/1/2024.
//

#ifndef OPENGL_MACAPP_SPOTLIGHT_H
#define OPENGL_MACAPP_SPOTLIGHT_H


#include <glm/vec3.hpp>
#include <GL/glew.h>
#include "PointLight.h"

class SpotLight : public PointLight {
private:
    glm::vec3 direction;
    GLfloat edge, processedEdge;

public:
    SpotLight();

    SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
              GLfloat xPosition, GLfloat yPosition, GLfloat zPosition,
              GLfloat xDirection, GLfloat yDirection, GLfloat zDirection,
              GLfloat constant, GLfloat linear, GLfloat exponent,
              GLfloat edge);


    void UseSpotLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
                      GLint diffuseIntensityLocation, GLint positionLocation, GLint directionLocation,
                      GLint constantLocation, GLint linearLocation, GLint exponentLocation,
                      GLint edgeLocation);

    void SetAsFlashLight(glm::vec3 position, glm::vec3 direction);

    ~SpotLight();
};


#endif //OPENGL_MACAPP_SPOTLIGHT_H
