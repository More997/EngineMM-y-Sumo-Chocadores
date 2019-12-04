#pragma once
#include "Composite.h"
#include "Mesher.h"
#include "Texture.h"
#include "Vertex.h"
#include "FVF.h"
#include "Camera.h"
class IMPORTEXPORT MeshRenderer :
	public Composite
{
private:
	Texture *theTexture; //Puntero a la textura. No se hace una por objeto.
	
	//Material* m_Material;
	
protected:
	
	Camera *theCamera;
public:
	Mesher *theMesher;
	Mesher* importedModel;
	MeshRenderer(Camera* _theCamera);
	MeshRenderer(Mesher* _importedModel);
	MeshRenderer(Mesher* comingMesher, Camera* _theCamera);
	MeshRenderer(Texture* thatTexture, Camera* _theCamera);
	MeshRenderer(Mesher* comingMesher, Texture* thatTexture, Camera* _theCamera);
	~MeshRenderer();
	void SetMesher(Mesher*_theMesher);
	Mesher* GetMesher();
	void defineTransformationMatrix();
	void SetTexture(Texture *tex); //NO USAR CON CLASES DERIVADAS, SOLO PARA ACORES BASE.
	BoundingBox GetMeshBoundingBox() override;
	Texture* GetTexture();
	bool BoxinFructrum();
	void Blending(int blendNumber);
	void RenderingComposite() override;
};


