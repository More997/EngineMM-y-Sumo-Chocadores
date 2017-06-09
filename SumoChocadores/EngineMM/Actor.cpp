#include "stdafx.h"
#include "Actor.h"

Actor::Actor()
{
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trasl);
	D3DXMatrixIdentity(&rotation);
}

void Actor::setModelPos(float transX, float transY, float transZ)
{
	D3DXMatrixTranslation(&trasl, transX, transY, transZ);
}

void Actor::setModelScale(float scaleX, float scaleY, float scaleZ)
{
	D3DXMatrixScaling(&scale, scaleX, scaleY, scaleZ); //Constructe de la matriz de escala, Ahorramos pasos y es mas seguro ;)
}
void Actor::setModelRot(float rotZ)
{
	D3DXMatrixRotationZ(&rotation, rotZ);
}
void Actor::defTransMat()
{
	D3DXMatrixIdentity(&matFinal);
	D3DXMatrixMultiply(&matFinal, &trasl, &matFinal);
	D3DXMatrixMultiply(&matFinal, &rotation, &matFinal);
	D3DXMatrixMultiply(&matFinal, &scale, &matFinal);
	//matFinal = scale * rotation * trasl;
}

Actor::Actor(LPDIRECT3DDEVICE9 dev)
{
}


Actor::~Actor()
{

}

void Actor::DrawV(LPDIRECT3DDEVICE9 dev)
{
	defTransMat();
	dev->SetFVF(CUSTOMFVF);
	//Multiplicación de Matrices
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

