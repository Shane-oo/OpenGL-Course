//
// Created by Shane Monck on 29/12/2023.
//
#define STB_IMAGE_IMPLEMENTATION

#include <GL/glew.h>
#include "Texture.h"

#include "Resources/SingleFileLibaries/stb_image.h"

Texture::Texture() {
    texture_Id = 0;
    width = 0;
    height = 0;
    bit_depth = 0;
    file_location = "";
}

Texture::Texture(const char *location) {
    texture_Id = 0;
    width = 0;
    height = 0;
    bit_depth = 0;
    file_location = location;
}


Texture::~Texture() {
    ClearTexture();
}

bool Texture::LoadTexture() {
    unsigned char *texture_data = stbi_load(file_location, &width, &height, &bit_depth, 0);
    if (!texture_data) {
        printf("Failed to find: %s\n", file_location);
        return false;
    }

    glGenTextures(1, &texture_Id);
    glBindTexture(GL_TEXTURE_2D, texture_Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D); // automatically generate mipmaps instead of providing

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texture_data);

    return true;
}

bool Texture::LoadTextureWithAlpha() {
    unsigned char *texture_data = stbi_load(file_location, &width, &height, &bit_depth, 0);
    if (!texture_data) {
        printf("Failed to find: %s\n", file_location);
        return false;
    }

    glGenTextures(1, &texture_Id);
    glBindTexture(GL_TEXTURE_2D, texture_Id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
    glGenerateMipmap(GL_TEXTURE_2D); // automatically generate mipmaps instead of providing

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(texture_data);

    return true;
}


void Texture::UseTexture() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_Id);
}

void Texture::ClearTexture() {
    glDeleteTextures(1, &texture_Id);
    texture_Id = 0;
    width = 0;
    bit_depth = 0;
    file_location = "";
}

