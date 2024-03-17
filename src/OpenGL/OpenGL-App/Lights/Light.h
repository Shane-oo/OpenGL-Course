//
// Created by Shane Monck on 29/12/2023.
//

#ifndef OPENGL_MACAPP_LIGHT_H
#define OPENGL_MACAPP_LIGHT_H

#include <GL/glew.h>
#include <glm/detail/type_mat4x4.hpp>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>
#include <optional>

#include "../ShadowMap.h"

class Light {
protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;

    GLfloat diffuseIntensity;
    
    glm::mat4 lightProj;
    ShadowMap* shadowMap;

    void UseLight(GLint ambientIntensityLocation, GLint ambientColourLocation,
                  GLint diffuseIntensityLocation);

public:
    Light();

    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
          GLsizei shadowWidth, GLsizei shadowHeight);

    ShadowMap* GetShadowMap(){return shadowMap;};
};


#endif //OPENGL_MACAPP_LIGHT_H
