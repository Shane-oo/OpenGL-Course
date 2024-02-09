//
// Created by ShaneMonck on 9/02/2024.
//

#ifndef OPENGL_MACAPP_MODEL_H
#define OPENGL_MACAPP_MODEL_H

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.h"
#include "Texture.h"

class Model {
private:
    std::vector<Mesh *> meshList;
    std::vector<Texture *> textureList;
    std::vector<unsigned int> meshToTexture;

    void LoadNode(aiNode *node, const aiScene *scene);

    void LoadMesh(aiMesh *mesh, const aiScene *scene);

    void LoadMaterials(const aiScene *scene);

public:
    Model();

    void LoadModel(const std::string &fileName);

    void RenderModel();

    void ClearModel();

    ~Model();
};


#endif //OPENGL_MACAPP_MODEL_H
