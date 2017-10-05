#ifndef MESHRENDER_H
#define MESHRENDER_H
#include "Composite.h"
#include "Textura.h"
class IMPORTEXPORT MeshRender :
	public Composite
{
private:
	Mesh* mesh2;
	Textura* texture;
public:
	MeshRender();
	MeshRender(Textura* tex);
	void SetTexture(Textura* tex);
	Textura* GetTexture();
	void SetMesh(Mesh* mesh);
	Mesh* GetMesh();
	~MeshRender();
	void RenderingComposite() override;
	void Blending(int numBlend);
	void Warping(int numWarp);
	void Filtro(int numfiltro);
};
#endif

