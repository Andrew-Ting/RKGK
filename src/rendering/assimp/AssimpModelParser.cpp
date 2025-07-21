
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "AssimpModelParser.h"

#include <iostream>
#include <stdexcept>



void AssimpModelParser::parseNewModel(const std::string& modelName, const std::string& filePath)
{
	modelMapping[modelName] = mImporter.ReadFile(filePath,
        aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType |
        aiProcess_ValidateDataStructure);
}

const std::vector<glm::vec3> AssimpModelParser::getModelVertexPositions(const std::string& modelName)
{
    if (!modelMapping[modelName])
    {
        throw std::logic_error("Trying to access a model that has not been loaded into the engine");
    }
    if (!modelMapping[modelName]->mRootNode)
    {
        throw std::runtime_error("The input model does not have a root node. Ensure the model was exported properly");
    }
    int numMeshes = modelMapping[modelName]->mNumMeshes;
    std::vector <glm::vec3> vertices;
    vertices.reserve(_getNumberOfVerticesTotal(modelName));
    int vertexIndex = 0;
	for (int i = 0; i < numMeshes; i++)
    {
		int numMeshVertices = modelMapping[modelName]->mMeshes[i]->mNumVertices;
        aiVector3D* meshVertices = modelMapping[modelName]->mMeshes[i]->mVertices;
        for (int j = 0; j < numMeshVertices; j++)
        {
            vertices.emplace_back(meshVertices[j].x, meshVertices[j].y, meshVertices[j].z);
        }
        vertexIndex += numMeshVertices;
    }
    return vertices;
}

const std::vector<glm::vec2> AssimpModelParser::getModelVertexUVs(const std::string& modelName)
{
    uint8_t numMeshes = modelMapping[modelName]->mNumMeshes;
    std::vector<glm::vec2> vertexUVs;
    vertexUVs.reserve(_getNumberOfVerticesTotal(modelName));
    for (uint8_t i = 0; i < numMeshes; i++) {
        for (uint8_t j = 1; j < AI_MAX_NUMBER_OF_TEXTURECOORDS; j++) {
            if (modelMapping[modelName]->mMeshes[i]->mTextureCoords[j] != nullptr)
            {
                throw std::runtime_error("Models with multiple UV coordinates are not yet supported. Please use the same UV mapping of a vertex for all textures it is in");
            }
        }
        if (modelMapping[modelName]->mMeshes[i]->mNumUVComponents[0] > 2)
        {
            throw std::runtime_error("Volumetric textures are not yet supported. :c");
        }
        uint32_t numVertices = modelMapping[modelName]->mMeshes[i]->mNumVertices;
        for (uint32_t vertexIndex = 0; vertexIndex < numVertices; vertexIndex++) {
            aiVector3D uv = modelMapping[modelName]->mMeshes[i]->mTextureCoords[0][vertexIndex];
            vertexUVs.emplace_back(uv.x, uv.y);
        }
    }
    return vertexUVs;
}

std::string AssimpModelParser::getModelTexturePath(const std::string& modelName, int textureIndex)
{
    if (modelMapping[modelName]->mNumMaterials > 1)
    {
        throw std::runtime_error("For simplicity, models with > 1 material are not supported. Please split meshes with different materials into different models");
    }
    if (textureIndex >= modelMapping[modelName]->mMaterials[0]->GetTextureCount(aiTextureType_BASE_COLOR))
    {
        throw std::runtime_error("Trying to query a texture index larger than the number of textures in the material");
    }
    for (aiTextureType textureType = aiTextureType_NONE; textureType <= AI_TEXTURE_TYPE_MAX; textureType = static_cast<aiTextureType>(textureType + 1))
    {
	    if (textureType != aiTextureType_BASE_COLOR)
	    {
            std::cerr << "The imported model contains a texture of type aiTextureType index " << static_cast<int>(textureType) << ", which is not supported and will therefore be ignored";
	    }
    }
	aiString texturePath;
    modelMapping[modelName]->mMaterials[0]->GetTexture( aiTextureType_BASE_COLOR, textureIndex, &texturePath);
    return texturePath.C_Str();

}

int AssimpModelParser::_getNumberOfVerticesTotal(const std::string& modelName)
{
    int numMeshes = modelMapping[modelName]->mNumMeshes;
    int vertexCount = 0;
    for (uint8_t i = 0; i < numMeshes; i++) {
        vertexCount += modelMapping[modelName]->mMeshes[i]->mNumVertices;
		if (vertexCount > MAX_VERTEX_COUNT)
		{
            throw std::runtime_error("Found a model unfit for real time rendering. Please reduce the number of vertices in the model.");
		}
    }
    return vertexCount;
}
