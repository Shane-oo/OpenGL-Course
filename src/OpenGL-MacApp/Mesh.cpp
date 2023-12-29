//
// Created by Shane Monck on 23/12/2023.
//

#include "Mesh.h"

Mesh::Mesh() {
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
}

Mesh::~Mesh() {
    ClearMesh();
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices) {

    indexCount = static_cast<GLsizei>(numOfIndices);

    // Generate a VAO ID.
    glGenVertexArrays(1, &VAO);
    // Bind the VAO with that ID
    glBindVertexArray(VAO);
    // Generate a IBO ID
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(sizeof(indices[0]) * numOfIndices),
                 indices,
                 GL_STATIC_DRAW);

    // Generate a VBO ID
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,
                 static_cast<GLsizeiptr>(sizeof(vertices[0]) * numOfVertices),
                 vertices,
                 GL_STATIC_DRAW);

    // Position vertices
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, nullptr);
    glEnableVertexAttribArray(0);

    // Texture UV vertices
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 5, (void *) (sizeof(vertices[0]) * 3));
    glEnableVertexAttribArray(1);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    // must bind before compiling shaders
    glBindVertexArray(VAO);
}


void Mesh::RenderMesh() {
    // bind the VAO
    glBindVertexArray(VAO);

    // bind the IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // draw
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);

    // unbind the IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // unbind the VAO
    glBindVertexArray(0);
}

void Mesh::ClearMesh() {
    if (IBO != 0) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if (VBO != 0) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (VAO != 0) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}





