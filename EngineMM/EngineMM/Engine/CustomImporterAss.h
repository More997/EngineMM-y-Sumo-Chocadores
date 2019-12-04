#ifndef CUSTOMIMPORTER_H
#define CUSTOMIMPORTER_H
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include "Game.h"
#include "BoundingBox.h"
class IMPORTEXPORT CustomImporterAss //THIS IS FOR ASSIMP IMPORTS
{
	BoundingBox bounding;
public:
	CustomImporterAss();
	~CustomImporterAss();
	bool ImportScene(const std::string& pFile);
};
#endif