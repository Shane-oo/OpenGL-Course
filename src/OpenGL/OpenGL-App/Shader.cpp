//
// Created by Shane Monck on 23/12/2023.
//

#include "Shader.h"
#include <cstdio>
#include <cstring>
#include <fstream>
#include <glm/gtc/type_ptr.hpp>

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

void Shader::AddShader(GLuint program, const char *shaderCode,
                       GLenum shaderType) {
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
  uniform_directional_light.uniform_color =
      glGetUniformLocation(shader_ID, "directional_light.base.colour");
  uniform_directional_light.uniform_ambient_intensity = glGetUniformLocation(
      shader_ID, "directional_light.base.ambient_intensity");
  uniform_directional_light.uniform_diffuse_intensity = glGetUniformLocation(
      shader_ID, "directional_light.base.diffuse_intensity");
  uniform_directional_light.uniform_direction =
      glGetUniformLocation(shader_ID, "directional_light.direction");
  uniform_specular_intensity =
      glGetUniformLocation(shader_ID, "material.specular_intensity");
  uniform_shininess = glGetUniformLocation(shader_ID, "material.shininess");
  uniform_eye_position = glGetUniformLocation(shader_ID, "eye_position");

  uniform_point_light_count =
      glGetUniformLocation(shader_ID, "point_light_count");

  for (size_t i = 0; i < MAX_POINT_LIGHTS; i++) {
    char location_buffer[100] = {'\0'};

    // point_lights[0].base.colour, point_lights[1].base.colour ...
    snprintf(location_buffer, sizeof(location_buffer),
             "point_lights[%zu].base.colour", i);
    uniform_point_light[i].uniform_color =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "point_lights[%zu].base.ambient_intensity", i);
    uniform_point_light[i].uniform_ambient_intensity =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "point_lights[%zu].base.diffuse_intensity", i);
    uniform_point_light[i].uniform_diffuse_intensity =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "point_lights[%zu].position", i);
    uniform_point_light[i].uniform_position =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "point_lights[%zu].constant", i);
    uniform_point_light[i].uniform_constant =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "point_lights[%zu].linear", i);
    uniform_point_light[i].uniform_linear =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "point_lights[%zu].exponent", i);
    uniform_point_light[i].uniform_exponent =
        glGetUniformLocation(shader_ID, location_buffer);
  }

  uniformSpotLightCount = glGetUniformLocation(shader_ID, "spotLightCount");

  for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++) {
    char location_buffer[100] = {'\0'};

    // point_lights[0].base.colour, point_lights[1].base.colour ...
    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].pointLight.base.colour", i);
    uniformSpotLights[i].uniform_color =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].pointLight.base.ambient_intensity", i);
    uniformSpotLights[i].uniform_ambient_intensity =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].pointLight.base.diffuse_intensity", i);
    uniformSpotLights[i].uniform_diffuse_intensity =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].pointLight.position", i);
    uniformSpotLights[i].uniform_position =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].pointLight.constant", i);
    uniformSpotLights[i].uniform_constant =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].pointLight.linear", i);
    uniformSpotLights[i].uniform_linear =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].pointLight.exponent", i);
    uniformSpotLights[i].uniform_exponent =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer),
             "spotLights[%zu].direction", i);
    uniformSpotLights[i].uniformDirection =
        glGetUniformLocation(shader_ID, location_buffer);

    snprintf(location_buffer, sizeof(location_buffer), "spotLights[%zu].edge",
             i);
    uniformSpotLights[i].uniformEdge =
        glGetUniformLocation(shader_ID, location_buffer);
  }

  uniformTexture = glGetUniformLocation(shader_ID, "theTexture");
  uniformDirectionalLightTransform =
      glGetUniformLocation(shader_ID, "directionalLightTransform");
  uniformDirectionalShadowMap =
      glGetUniformLocation(shader_ID, "directionalShadowMap");
}

Shader::Shader() {
  shader_ID = 0;
  uniform_model = 0;
  uniform_projection = 0;
  uniform_view = 0;

  uniformTexture = 0;
  uniformDirectionalLightTransform = 0;
  uniformDirectionalShadowMap = 0;

  point_light_count = 0;
  spotLightCount = 0;
}

Shader::~Shader() { ClearShader(); }

GLint Shader::GetUniformProjection() const { return uniform_projection; }

GLint Shader::GetUniformModel() const { return uniform_model; }

GLint Shader::GetUniformView() const { return uniform_view; }

GLint Shader::GetUniformSpecularIntensity() const {
  return uniform_specular_intensity;
}

GLint Shader::GetUniformShininess() const { return uniform_shininess; }

GLint Shader::GetUniformEyePosition() const { return uniform_eye_position; }

void Shader::CreateFromString(const char *vertexCode,
                              const char *fragmentCode) {
  CompileShader(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char *vertexName, const char *fragmentName) {
  std::string vertexString = ReadFile(vertexName);
  std::string fragmentString = ReadFile(fragmentName);
  const char *vertexCode = vertexString.c_str();
  const char *fragmentCode = fragmentString.c_str();

  CompileShader(vertexCode, fragmentCode);
}

void Shader::UseShader() { glUseProgram(shader_ID); }

void Shader::SetDirectionalLight(DirectionalLight *directional_light) {
  directional_light->UseDirectionalLight(
      uniform_directional_light.uniform_ambient_intensity,
      uniform_directional_light.uniform_color,
      uniform_directional_light.uniform_diffuse_intensity,
      uniform_directional_light.uniform_direction);
}

void Shader::SetPointLights(PointLight *point_lights, GLint light_count) {
  if (light_count > MAX_POINT_LIGHTS) {
    light_count = MAX_POINT_LIGHTS;
  }

  glUniform1i(uniform_point_light_count, light_count);

  for (size_t i = 0; i < light_count; i++) {
    point_lights[i].UsePointLight(
        uniform_point_light[i].uniform_ambient_intensity,
        uniform_point_light[i].uniform_color,
        uniform_point_light[i].uniform_diffuse_intensity,
        uniform_point_light[i].uniform_position,
        uniform_point_light[i].uniform_constant,
        uniform_point_light[i].uniform_linear,
        uniform_point_light[i].uniform_exponent);
  }
}

void Shader::SetSpotLights(SpotLight *spotLights, GLint lightCount) {
  if (lightCount > MAX_SPOT_LIGHTS) {
    lightCount = MAX_SPOT_LIGHTS;
  }

  glUniform1i(uniformSpotLightCount, lightCount);

  for (size_t i = 0; i < lightCount; i++) {
    spotLights[i].UseSpotLight(uniformSpotLights[i].uniform_ambient_intensity,
                               uniformSpotLights[i].uniform_color,
                               uniformSpotLights[i].uniform_diffuse_intensity,
                               uniformSpotLights[i].uniform_position,
                               uniformSpotLights[i].uniformDirection,
                               uniformSpotLights[i].uniform_constant,
                               uniformSpotLights[i].uniform_linear,
                               uniformSpotLights[i].uniform_exponent,
                               uniformSpotLights[i].uniformEdge);
  }
}

void Shader::ClearShader() {
  if (shader_ID != 0) {
    glDeleteProgram(shader_ID);
    shader_ID = 0;
  }

  uniform_model = 0;
  uniform_projection = 0;
  uniform_view = 0;
  uniform_directional_light.uniform_color = 0;
  uniform_directional_light.uniform_ambient_intensity = 0;
  uniform_directional_light.uniform_diffuse_intensity = 0;
  uniform_directional_light.uniform_direction = 0;
  uniform_specular_intensity = 0;
  uniform_shininess = 0;

  for (auto &i : uniform_point_light) {
    i.uniform_color = 0;
    i.uniform_ambient_intensity = 0;
    i.uniform_diffuse_intensity = 0;
    i.uniform_position = 0;
    i.uniform_constant = 0;
    i.uniform_linear = 0;
    i.uniform_exponent = 0;
  }

  for (auto &i : uniformSpotLights) {
    i.uniform_color = 0;
    i.uniform_ambient_intensity = 0;
    i.uniform_diffuse_intensity = 0;
    i.uniform_position = 0;
    i.uniform_constant = 0;
    i.uniform_linear = 0;
    i.uniform_exponent = 0;
    i.uniformDirection = 0;
    i.uniformEdge = 0;
  }
}
void Shader::SetTexture(GLint textureUnit) {
  glUniform1i(uniformTexture, textureUnit);
}
void Shader::SetDirectionalShadowMap(GLint textureUnit) {
  glUniform1i(uniformDirectionalShadowMap, textureUnit);
}
void Shader::SetDirectionalLightSpaceTransform(glm::mat4 lightTransform) {
  glUniformMatrix4fv(uniformDirectionalLightTransform, 1, GL_FALSE,
                     glm::value_ptr(lightTransform));
}
