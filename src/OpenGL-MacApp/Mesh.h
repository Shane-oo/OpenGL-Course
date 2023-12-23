//
// Created by Shane Monck on 23/12/2023.
//

#ifndef OPENGL_MACAPP_MESH_H
#define OPENGL_MACAPP_MESH_H


#include <GL/glew.h>

class Mesh {
private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
public:
    Mesh(); // constructor
    ~Mesh(); // destructor

    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);

    void RenderMesh();

    void ClearMesh();
};


#endif //OPENGL_MACAPP_MESH_H
