#include "stdafx.h"
#include "ImporterAssimp.h"


ImporterAssimp::ImporterAssimp()
{
}


ImporterAssimp::~ImporterAssimp()
{
}

void ImporterAssimp::usingImporter(const string& pFile)
{
	Importer importer;
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);
	if (!scene)
		cout << "Cant use the scene" << endl;
	else
		cout << "Using the scene" << endl;

}

Mesh * ImporterAssimp::getModel3D() const
{
	return model3D;
}
