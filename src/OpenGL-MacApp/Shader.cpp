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
    std::string shaderLocation = "Resources/Shaders/" + std::string(shaderName);

    std::ifstream fileStream(shaderLocation, std::ios::in);

    if (!fileStream.is_open()) {
        printf("Failed to read %s File doesn't exist", shaderLocation.c_str());
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
    shader_ID = glCreateProgram();

    if (!shader_ID) {
        printf("Error creating shader program! \n");
        return;
    }

    AddShader(shader_ID, vShader, GL_VERTEX_SHADER);
    AddShader(shader_ID, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader_ID);
    glGetProgramiv(shader_ID, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader_ID, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: '%s' \n", eLog);
        return;
    }

    glValidateProgram(shader_ID);
    glGetProgramiv(shader_ID, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(shader_ID, sizeof(eLog), nullptr, eLog);
        printf("Error Validating program: '%s' \n", eLog);
        return;
    }

    printf("Compiled Successfully\n");

    uniform_model = glGetUniformLocation(shader_ID, "model");
    uniform_projection = glGetUniformLocation(shader_ID, "projection");
    uniform_view = glGetUniformLocation(shader_ID, "view");
}


Shader::Shader() {
    shader_ID = 0;
    uniform_model = 0;
    uniform_projection = 0;
    uniform_view = 0;
}

Shader::~Shader() {
    ClearShader();
}

int Shader::GetUniformProjection() const {
    return uniform_projection;
}

int Shader::GetUniformModel() const {
    return uniform_model;
}

int Shader::GetUniformView() const {
    return uniform_view;
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


void Shader::UseShader() {
    glUseProgram(shader_ID);
}

void Shader::ClearShader() {
    if (shader_ID != 0) {
        glDeleteProgram(shader_ID);
        shader_ID = 0;
    }

    uniform_model = 0;
    uniform_projection = 0;
}




