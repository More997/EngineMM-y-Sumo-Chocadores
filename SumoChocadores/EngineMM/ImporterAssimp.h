#ifndef IMPORTERASSIMP_H
#define IMPORTERASSIMP_H
#include <iostream>
#include <assimp\Importer.hpp>
#include <assimp\cimport.h>
#include <assimp/scene.h>          
#include <assimp/postprocess.h>  
using namespace Assimp;
using namespace std;
class IMPORTEXPORT ImporterAssimp
{
public:
	ImporterAssimp();
	~ImporterAssimp();
	void usingImporter(const string& pFile);
};
#endif

