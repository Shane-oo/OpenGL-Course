//
// Created by ShaneMonck on 9/02/2024.
//

#include "Model.h"

void Model::LoadNode(aiNode *node, const aiScene *scene) {
    for (size_t i = 0; i < node->mNumMeshes; i++) {
        unsigned int meshId = node->mMeshes[i];
        LoadMesh(scene->mMeshes[meshId], scene);
    }

    for (size_t i = 0; i < node->mNumChildren; i++) {
        LoadNode(node->mChildren[i], scene);
    }
}


void Model::LoadMesh(aiMesh *mesh, const aiScene *scene) {
    std::vector<GLfloat> vertices;
    st
}


void Model::LoadMaterials(const aiScene *scene) {

}


Model::Model() {

}

Model::~Model() {

}

void Model::LoadModel(const std::string &fileName) {
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName, aiProcess_Triangulate
                                                       | aiProcess_FlipUVs
                                                       | aiProcess_GenSmoothNormals
                                                       | aiProcess_JoinIdenticalVertices);

    if (!scene) {
        printf("Model (%s) failed to load: %s", fileName.c_str(), importer.GetErrorString());
        return;
    }

    LoadNode(scene->mRootNode, scene);

    LoadMaterials(scene);
}

void Model::RenderModel() {

}

void Model::ClearModel() {

}

