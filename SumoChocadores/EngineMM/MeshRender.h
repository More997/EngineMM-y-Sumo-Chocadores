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
	void defTransMat();
	void RenderingComposite() override;
	void Blending(int numBlend); //numero del 0 al 2
	void Warping(int numWarp);//numero del 1 al 6
	void Filtro(int numfiltro);//numero del 1 al 7
	BoundingBox GetMeshBB() override;
	void BuildViewFrustum(D3DMATRIX _projection, D3DMATRIX _view); //Tiene que tener acceso al Projection.
};
#endif

