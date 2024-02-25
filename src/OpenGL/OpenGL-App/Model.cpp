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
    std::vector<unsigned int> indices;

    for (size_t i = 0; i < mesh->mNumVertices; i++) {
        vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
        if (mesh->mTextureCoords[0]) {
            vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
            
        }
        else {
            vertices.insert(vertices.end(), { 0, 0 });
        }
        vertices.insert(vertices.end(), { mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z });
    }

    for (size_t i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    Mesh* newMesh = new Mesh();
    newMesh->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size());
    meshList.push_back(newMesh);
    meshToTexture.push_back(mesh->mMaterialIndex);
}


void Model::LoadMaterials(const aiScene *scene) {
    textureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; i++) {
        aiMaterial* material = scene->mMaterials[i];
        // todo this is where i am
    }
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

