//
// Created by Shane Monck on 23/12/2023.
//

#ifndef OPENGL_MACAPP_SHADER_H
#define OPENGL_MACAPP_SHADER_H


#include <GL/glew.h>
#include <string>

class Shader {
private:
    GLuint shaderID;
    int uniformProjection, uniformModel;

    void CompileShader(const char *vShader, const char *fShader);

    void AddShader(GLuint program, const char *shaderCode, GLenum shaderType);

    static std::string ReadFile(const char* shaderName);

public:
    Shader();

    ~Shader();

    void CreateFromString(const char *vertexCode, const char *fragmentCode);

    void CreateFromFiles(const char *vertexName, const char *fragmentName);


    int GetUniformProjection() const;

    int GetUniformModel() const;

    void UseShader();

    void ClearShader();

};


#endif //OPENGL_MACAPP_SHADER_H
