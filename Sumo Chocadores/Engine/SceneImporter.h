#ifndef SCENEIMPORTER_H
#define SCENEIMPORTER_H
#include "EngineApi.h"
#include "Composite.h"
#include <iostream>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class IMPORTEXPORT SceneImporter
{
public:
	void Import(const std::string& filename, Composite* root, LPDIRECT3DDEVICE9 dev);
	void ImportChildren(aiNode* child, Composite* parent, const aiScene* scene, LPDIRECT3DDEVICE9 dev);
};

#endif

