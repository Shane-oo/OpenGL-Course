//
// Created by Shane Monck on 3/1/2024.
//

#include <glm/trigonometric.hpp>
#include <glm/geometric.hpp>
#include "SpotLight.h"

SpotLight::SpotLight() : PointLight() {
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    edge = 0.0f;
    processedEdge = cosf(glm::radians(edge));
}


SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
                     GLfloat xPosition, GLfloat yPosition, GLfloat zPosition,
                     GLfloat xDirection, GLfloat yDirection, GLfloat zDirection,
                     GLfloat constant, GLfloat linear, GLfloat exponent,
                     GLfloat edge) : PointLight(red, green, blue, ambientIntensity, diffuseIntensity,
                                                xPosition, yPosition, zPosition,
                                                constant, linear, exponent) {
    direction = glm::normalize(glm::vec3(xDirection, yDirection, zDirection));
    this->edge = edge;
    processedEdge = cosf(glm::radians(edge));
}

SpotLight::~SpotLight() {

}

void SpotLight::UseSpotLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
                             GLint diffuseIntensityLocation, GLint positionLocation, GLint directionLocation,
                             GLint constantLocation, GLint linearLocation, GLint exponentLocation,
                             GLint edgeLocation) {
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation, processedEdge);

    UsePointLight(ambientIntensityLocation, ambientColourLocation,
                  diffuseIntensityLocation, positionLocation,
                  constantLocation, linearLocation, exponentLocation);
}

void SpotLight::SetAsFlashLight(glm::vec3 position, glm::vec3 direction) {
    position.y -= 0.3f;

    this->position = position;
    this->direction = direction;
}
