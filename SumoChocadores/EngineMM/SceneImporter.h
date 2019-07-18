#ifndef SCENEIMPORTER_H
#define SCENEIMPORTER_H
#include <iostream>
#include "Game.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <list>
//#include "Camera.h"

using namespace std;
class IMPORTEXPORT SceneImporter
{
private:
	Game*s;
	list<Composite*> importedObjectsToDraw;
public:
	SceneImporter();
	~SceneImporter();
	void ImportScene(const string& pFile, Composite* root, Camera* objectCamera);
	void ImportChildren(aiNode* child, Composite* parent, const aiScene *scene, Camera *objectCamera);
};
#endif
