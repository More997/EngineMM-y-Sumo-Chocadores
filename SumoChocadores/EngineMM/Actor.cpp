#include "stdafx.h"
#include "Actor.h"

Actor::Actor()
{
}


Actor::Actor(LPDIRECT3DDEVICE9 dev)
{
}


Actor::~Actor()
{

}

void Actor::DrawV(LPDIRECT3DDEVICE9 dev, D3DXMATRIX _trasl, D3DXMATRIX _scale,
	D3DXMATRIX _rotation)
{

	dev->SetFVF(CUSTOMFVF);

	D3DXMATRIX trasl = _trasl;
	D3DXMATRIX scale = _scale;
	D3DXMATRIX rotation = _rotation;
	//Multiplicación de Matrices
	D3DXMATRIX matFinal;
	D3DXMatrixIdentity(&matFinal);
	matFinal = scale * rotation * trasl; //Primero se escala, despues se rota y despues se traslada.


										 //Le digo a la placa que la matriz de mundo es "mat"
	dev->SetTransform(D3DTS_WORLD, &matFinal);

	dev->SetFVF(CUSTOMFVF);
	dev->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));
	dev->SetIndices(mesh2->GetInd());
	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);


	//Especificamos cual VB vamos a usar
	dev->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));

	//Especificamos indices
	dev->SetIndices(mesh2->GetInd());

	//dibujamos
	dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
}
void Actor::SetMesh(Mesh * mesh)
{
	mesh2 = mesh;
}

void Actor::Move(LPDIRECT3DDEVICE9 dev)
{
	float PosZ = 0;
	float RotX = 0;
	D3DXMATRIX _transl;
	D3DXMatrixIdentity(&_transl);
	_transl._41 = 0;	//Esto mueve en X (columna 4, fila 1)
	_transl._42 = 0;	//Esto mueve en Y (columna 4, fila 2)
	_transl._43 = PosZ;	//Esto mueve en Z (columna 4, fila 3)
	D3DXMATRIX _scale;
	D3DXMatrixIdentity(&_scale);
	_scale._11 = 1.0f;
	_scale._22 = 1.0f;
	_scale._33 = 1.0f;
	D3DXMATRIX _rotation;
	D3DXMatrixIdentity(&_rotation);
	_rotation._11 = cos(D3DXToRadian(RotX));
	_rotation._12 = sin(D3DXToRadian(RotX));
	_rotation._21 = -sin(D3DXToRadian(RotX));
	_rotation._22 = cos(D3DXToRadian(RotX));

	PosZ += 0.01;
	RotX += -0.50;
	DrawV(dev, _transl, _scale, _rotation);
}
