//
// Created by Shane on 17/03/2024.
//

#include "ShadowMap.h"
#include <cstdio>

ShadowMap::ShadowMap() {
  FBO = 0;
  shadowMap = 0;
}

ShadowMap::~ShadowMap() {
  if (FBO) {
    glDeleteFramebuffers(1, &FBO);
  }

  if (shadowMap) {
    glDeleteTextures(1, &shadowMap);
  }
}

bool ShadowMap::Init(GLsizei width, GLsizei height) {
  shadowWidth = width;
  shadowHeight = height;

  glGenFramebuffers(1, &FBO);

  glGenTextures(1, &shadowMap);
  glBindTexture(GL_TEXTURE_2D, shadowMap);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, shadowWidth, shadowHeight,
               0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
  float bColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
  glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, bColor);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
  glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,
                         shadowMap, 0);

  // specify not to use colour
  glDrawBuffer(GL_NONE);
  glReadBuffer(GL_NONE);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE) {
    printf("Framebuffer Error:%i\n", status);
    return false;
  }

  return true;
}

void ShadowMap::Write() { glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO); }

void ShadowMap::Read(GLenum textureUnit) {
  glActiveTexture(textureUnit);
  glBindTexture(GL_TEXTURE_2D, shadowMap);
}