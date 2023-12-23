//
// Created by Shane Monck on 23/12/2023.
//

#include <cstdio>
#include <cstring>
#include <fstream>
#include "Shader.h"

std::string Shader::ReadFile(const char *shaderName) {
    std::string content;

    // Prefix "Shaders" to shaderName
    std::string shaderLocation = "Shaders/" + std::string(shaderName);

    std::ifstream fileStream(shaderLocation, std::ios::in);

    if (!fileStream.is_open()) {
        printf("Failed to read %s! File doesn't exist", shaderLocation.c_str());
        return "";
    }

    std::string line;
    while (std::getline(fileStream, line)) {
        content.append(line + "\n");
    }
    fileStream.close();

    return content;
}

void Shader::AddShader(GLuint program, const char *shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    const GLchar *code[1];
    code[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = static_cast<GLint>(strlen(shaderCode));

    glShaderSource(theShader, 1, code, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result) {
        glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        printf("Error compiling the %d shader: '%s' \n", shaderType, eLog);
        return;
    }

    glAttachShader(program, theShader);
}

void Shader::CompileShader(const char *vShader, const char *fShader) {
    shaderID = glCreateProgram();

    if (!shaderID) {
        printf("Error creating shader program! \n");
        return;
    }

    AddShader(shaderID, vShader, GL_VERTEX_SHADER);
    AddShader(shaderID, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: '%s' \n", eLog);
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error Validating program: '%s' \n", eLog);
        return;
    }

    printf("Compiled Successfully\n");

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
}


Shader::Shader() {
    shaderID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

Shader::~Shader() {
    ClearShader();
}

void Shader::CreateFromString(const char *vertexCode, const char *fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char *vertexName, const char *fragmentName) {
    std::string vertexString = ReadFile(vertexName);
    std::string fragmentString = ReadFile(fragmentName);
    const char *vertexCode = vertexString.c_str();
    const char *fragmentCode = fragmentString.c_str();

    CompileShader(vertexCode, fragmentCode);
}

int Shader::GetUniformProjection() const {
    return uniformProjection;
}

int Shader::GetUniformModel() const {
    return uniformModel;
}

void Shader::UseShader() {
    glUseProgram(shaderID);
}

void Shader::ClearShader() {
    if (shaderID != 0) {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
}




