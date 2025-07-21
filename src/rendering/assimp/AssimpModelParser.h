#pragma once

#include <map>
#include <assimp/Importer.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

class AssimpModelParser
{
	Assimp::Importer mImporter;
	std::map<std::string, const aiScene*> modelMapping;
public:
	AssimpModelParser() = default;
	void parseNewModel(const std::string& modelName, const std::string& filePath);
	const std::vector<glm::vec3> getModelVertexPositions(const std::string& modelName);
	const std::vector<glm::vec2> getModelVertexUVs(const std::string& modelName);
	std::string getModelTexturePath(const std::string& modelName, int textureIndex);

private:
	static const int MAX_VERTEX_COUNT = 1000000000;
	int _getNumberOfVerticesTotal(const std::string& modelName);
};
