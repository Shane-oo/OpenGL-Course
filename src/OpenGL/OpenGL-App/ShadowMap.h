//
// Created by Shane on 17/03/2024.
//

#ifndef OPENGL_SHADOWMAP_H
#define OPENGL_SHADOWMAP_H

#include <GL/glew.h>

class ShadowMap {
protected:
  GLuint FBO, shadowMap;
  GLsizei shadowWidth, shadowHeight;

public:
  ShadowMap();

  virtual bool Init(GLsizei width, GLsizei height);

  virtual void Write();

  virtual void Read(GLenum textureUnit);

  GLsizei GetShadowWidth() const { return shadowWidth; }

  GLsizei GetShadowHeight() const { return shadowHeight; }

  ~ShadowMap();
};

#endif // OPENGL_SHADOWMAP_H
