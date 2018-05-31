#ifndef IMPORTERASSIMP_H
#define IMPORTERASSIMP_H
#include <assimp\Importer.hpp>
#include <assimp/scene.h>          
#include <assimp/postprocess.h>  
#include <iostream>
using namespace Assimp;
using namespace std;
class ImporterAssimp
{
public:

	ImporterAssimp();
	~ImporterAssimp();
	void usingImporter(const string& pFile);
};
#endif

