//
// Created by Shane Monck on 30/12/2023.
//

#include "Material.h"


Material::Material() {
    specularIntensity = 0.0f;
    shininess = 0.0f;
}

Material::Material(GLfloat specularIntensity, GLfloat shininess) {
    this->specularIntensity = specularIntensity;
    this->shininess = shininess;
}

Material::~Material() {

}

void Material::UseMaterial(GLint specularIntensityLocation, GLint shininessLocation) {
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
