#include "stdafx.h"
#include "Actor.h"

Actor::Actor() :vector (0,0,0)
{
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trasl);
	D3DXMatrixIdentity(&rotation);
	defTransMat();
}
Actor::Actor(Textura* tex)
{
	D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trasl);
	D3DXMatrixIdentity(&rotation);
	texture = tex;
	defTransMat();
}
void Actor::setModelPos(float transX, float transY, float transZ)
{
	vector.x = transX;
	vector.y = transY;
	vector.z = transZ;
	D3DXMatrixTranslation(&trasl, transX, transY, transZ);
}

void Actor::setModelScale(float scaleX, float scaleY, float scaleZ)
{
	D3DXMatrixScaling(&scale, scaleX, scaleY, scaleZ); //Constructe de la matriz de escala, Ahorramos pasos y es mas seguro ;)
}
void Actor::setModelRotZ(float rotZ)
{
	D3DXMatrixRotationZ(&rotation, rotZ);
}
void Actor::setModelRotY(float rotY)
{
	D3DXMatrixRotationY(&rotation, rotY);
}
void Actor::setModelRotX(float rotX)
{
	D3DXMatrixRotationX(&rotation, rotX);

}
D3DXVECTOR3 Actor::getVector()
{
	return vector; //ACA TAAAA
}
void Actor::setVector(D3DXVECTOR3 _vector)
{
	setModelPos(_vector.x, _vector.y, _vector.z);
}
void Actor::defTransMat()
{
	/*D3DXMatrixIdentity(&matFinal);
	D3DXMatrixMultiply(&matFinal, &scale, &matFinal);
	D3DXMatrixMultiply(&matFinal, &rotation, &matFinal);
	D3DXMatrixMultiply(&matFinal, &trasl, &matFinal);*/
	matFinal = scale * rotation * trasl;
}


Actor::Actor(LPDIRECT3DDEVICE9 dev)
{
}


Actor::~Actor()
{

}

void Actor::DrawV(LPDIRECT3DDEVICE9 dev, int typeblend)
{
	if (texture != NULL)
		dev->SetTexture(0, texture->GetText());
	else
		dev->SetTexture(0, NULL);
	Blending(typeblend, dev);
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
void Actor::Blending(int numBlend, LPDIRECT3DDEVICE9 dev)
{
	switch (numBlend)
		{
		case 0://Aditivo
			dev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			break;
		case 1: //Multiplicativo
			dev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
			break;
		case 2://alphaBlending
			dev->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
			dev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			dev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		default:
			dev->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
			break;
		}
	}




