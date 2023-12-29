//
// Created by Shane Monck on 29/12/2023.
//

#ifndef OPENGL_MACAPP_TEXTURE_H
#define OPENGL_MACAPP_TEXTURE_H


class Texture {
private:
    GLuint texture_Id;
    int width, height, bit_depth;

    const char *file_location;

public:
    Texture();

    Texture(const char *location);

    ~Texture();

    void LoadTexture();

    void UseTexture();

    void ClearTexture();
};


#endif //OPENGL_MACAPP_TEXTURE_H
