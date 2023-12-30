//
// Created by Shane Monck on 30/12/2023.
//

#ifndef OPENGL_MACAPP_MATERIAL_H
#define OPENGL_MACAPP_MATERIAL_H


#include <GL/glew.h>

class Material {
private:
    GLfloat specularIntensity;
    GLfloat shininess;
public:
    Material();

    Material(GLfloat specularIntensity, GLfloat shininess);

    ~Material();

    void UseMaterial(GLint specularIntensityLocation, GLint shininessLocation);
};


#endif //OPENGL_MACAPP_MATERIAL_H
