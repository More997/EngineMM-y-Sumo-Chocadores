#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "Composite.h"
#include"FVF.h"
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include "EngineApi.h"
#include "Material.h"
#include "BoundingBox.h"

class Model;

class IMPORTEXPORT MeshRenderer : public Component
{
public:
	Material* m_Material;
	Model* m_Model;
	D3DXVECTOR2 _posUV;
	float _rotUV;
	MeshRenderer(Model* _model, Material* _material);
	~MeshRenderer();
	virtual void DibujarMesh(LPDIRECT3DDEVICE9 dev);

	void UpdateComposite();
};

#endif