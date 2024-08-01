#ifndef TEXTURE_H
#define TEXTURE_H

#include "window.h"

class Texture {
  unsigned int textureAddress;
  unsigned char* tempData;
  int width, height, nrChannels;
  GLenum textureUnit;

 public:
  Texture(std::string textureLocation, GLenum format, GLenum unit);
  void active() const;
};

#endif  // !TEXTURE_H