#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string textureLocation, GLenum format, GLenum unit)
    : textureUnit(unit) {
  glGenTextures(1, &this->textureAddress);
  glBindTexture(GL_TEXTURE_2D, this->textureAddress);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  this->tempData = stbi_load(textureLocation.c_str(), &this->width,
                             &this->height, &this->nrChannels, 0);

  if (this->tempData) {
    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
                 GL_UNSIGNED_BYTE, this->tempData);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    throw std::runtime_error("Texture at " + textureLocation +
                             " failed to load\n");
  }
  stbi_image_free(this->tempData);
}

void Texture::active() const {
  glActiveTexture(this->textureUnit);
  glBindTexture(GL_TEXTURE_2D, this->textureAddress);
}