#include <iostream> //FOR COUT
#include "stdafx.h"
#include "CustomImporterAss.h"



CustomImporterAss::CustomImporterAss()
{
}

bool CustomImporterAss::ImportScene(const std::string& pFile)
{
	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	//bounding.xMin = scene.

	// = xMin = min(position.x, boundi.xMin); // ?????????

	// If the import failed, report it
	if (!scene)
	{
		//DoTheErrorLogging(importer.GetErrorString());

		std::cout << "Import test failed" << std::endl;

		return false;
	}
	// Now we can access the file's contents.

	//Assimp //DoTheSceneProcessing(scene);
	std::cout << "Import test worked" << std::endl;

	// We're done. Everything will be cleaned up by the importer destructor
	return true;
}


CustomImporterAss::~CustomImporterAss()
{
}