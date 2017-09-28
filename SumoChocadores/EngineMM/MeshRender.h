#ifndef MESHRENDER_H
#define MESHRENDER_H
#include "Composite.h"
class MeshRender :
	public Composite
{
private:
	Mesh* mesh2;
	Textura* texture;
public:
	IMPORTEXPORT MeshRender();
	IMPORTEXPORT MeshRender(Textura* tex);
	IMPORTEXPORT void SetMesh(Mesh* mesh);
	IMPORTEXPORT Mesh* GetMesh();
	IMPORTEXPORT ~MeshRender();
	IMPORTEXPORT void RenderingComposite() override;
	IMPORTEXPORT void Blending(int numBlend);
};
#endif

