//
// Created by Shane Monck on 23/12/2023.
//

#ifndef OPENGL_MACAPP_SHADER_H
#define OPENGL_MACAPP_SHADER_H


#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint shader_ID;
    GLint uniform_projection, uniform_model, uniform_view, uniform_eye_position,
            uniform_ambient_intensity, uniform_ambient_colour, uniform_diffuse_intensity, uniform_direction,
            uniform_specular_intensity, uniform_shininess;

    void CompileShader(const char *vShader, const char *fShader);

    void AddShader(GLuint program, const char *shaderCode, GLenum shaderType);

    static std::string ReadFile(const char *shaderName);

public:
    Shader();

    ~Shader();

    GLint GetUniformProjection() const;

    GLint GetUniformModel() const;

    GLint GetUniformView() const;

    GLint GetUniformAmbientIntensity() const;

    GLint GetUniformAmbientColour() const;

    GLint GetUniformDiffuseIntensity() const;

    GLint GetUniformDirection() const;

    GLint GetUniformSpecularIntensity() const;

    GLint GetUniformShininess() const;

    GLint GetUniformEyePosition() const;

    void CreateFromString(const char *vertexCode, const char *fragmentCode);

    void CreateFromFiles(const char *vertexName, const char *fragmentName);

    void UseShader();

    void ClearShader();

};


#endif //OPENGL_MACAPP_SHADER_H
