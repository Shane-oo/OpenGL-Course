//
// Created by Shane Monck on 23/12/2023.
//

#ifndef OPENGL_MACAPP_SHADER_H
#define OPENGL_MACAPP_SHADER_H

#include "CommonValues.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include <GL/glew.h>
#include <glm/fwd.hpp>
#include <string>

class Shader {
private:
  GLuint shader_ID;

  GLint uniform_projection, uniform_model, uniform_view, uniform_eye_position,
      uniform_specular_intensity, uniform_shininess,
      uniformTexture,
      uniformDirectionalLightTransform, uniformDirectionalShadowMap;

  int point_light_count;
  int spotLightCount;
  GLint uniform_point_light_count;
  GLint uniformSpotLightCount;

  struct {
    GLint uniform_color;
    GLint uniform_ambient_intensity;
    GLint uniform_diffuse_intensity;

    GLint uniform_direction;
  } uniform_directional_light;

  struct {
    GLint uniform_color;
    GLint uniform_ambient_intensity;
    GLint uniform_diffuse_intensity;

    GLint uniform_position;
    GLint uniform_constant;
    GLint uniform_linear;
    GLint uniform_exponent;
  } uniform_point_light[MAX_POINT_LIGHTS];

  struct {
    GLint uniform_color;
    GLint uniform_ambient_intensity;
    GLint uniform_diffuse_intensity;

    GLint uniform_position;
    GLint uniform_constant;
    GLint uniform_linear;
    GLint uniform_exponent;

    GLint uniformDirection;
    GLint uniformEdge;
  } uniformSpotLights[MAX_SPOT_LIGHTS];

  void CompileShader(const char *vShader, const char *fShader);

  void AddShader(GLuint program, const char *shaderCode, GLenum shaderType);

  static std::string ReadFile(const char *shaderName);

public:
  Shader();

  ~Shader();

  GLint GetUniformProjection() const;

  GLint GetUniformModel() const;

  GLint GetUniformView() const;

  GLint GetUniformSpecularIntensity() const;

  GLint GetUniformShininess() const;

  GLint GetUniformEyePosition() const;

  void CreateFromString(const char *vertexCode, const char *fragmentCode);

  void CreateFromFiles(const char *vertexName, const char *fragmentName);

  void UseShader();

  void SetDirectionalLight(DirectionalLight *directional_light);

  void SetPointLights(PointLight *point_lights, GLint light_count);

  void SetSpotLights(SpotLight *spotLights, GLint lightCount);
  
  void SetTexture(GLint textureUnit);
  
  void SetDirectionalShadowMap(GLint textureUnit);
  
  void SetDirectionalLightSpaceTransform(glm::mat4 lTransform);

  void ClearShader();
};

#endif // OPENGL_MACAPP_SHADER_H
