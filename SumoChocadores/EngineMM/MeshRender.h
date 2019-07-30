#ifndef MESHRENDER_H
#define MESHRENDER_H
#include "Composite.h"
#include "Textura.h"
/*#include "FVF.h"
#include "Camera.h"
#include "Vertex.h"*/
class IMPORTEXPORT MeshRender :
	public Composite
{
private:
	Mesh* mesh2;
	Textura* texture;
	bool draw;
	Mesh* model;
protected:
	Camera * cam;
public:
	MeshRender();
	MeshRender(Textura* tex);
	MeshRender(Camera* _cam);
	MeshRender(Mesh* comingMesh, Camera* _cam);
	MeshRender(Textura* tex, Camera* _cam);
	MeshRender(Mesh* _mesh, Textura* tex, Camera* _cam);
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
	void setCamera(Camera* _cam);
	bool inFrustum();
};
#endif

