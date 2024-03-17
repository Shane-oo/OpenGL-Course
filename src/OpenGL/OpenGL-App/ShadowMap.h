//
// Created by Shane on 17/03/2024.
//

#ifndef OPENGL_SHADOWMAP_H
#define OPENGL_SHADOWMAP_H

#include <GL/glew.h>

class ShadowMap {
protected:
  GLuint FBO, shadowMap;
  GLuint shadowWidth, shadowHeight;

public:
  ShadowMap();

  virtual bool Init(GLuint width, GLuint height);

  virtual void Write();

  virtual void Read(GLenum textureUnit);

  GLuint GetShadowWidth() const { return shadowWidth; }

  GLuint GetShadowHeight() const { return shadowHeight; }

  ~ShadowMap();
};

#endif // OPENGL_SHADOWMAP_H
