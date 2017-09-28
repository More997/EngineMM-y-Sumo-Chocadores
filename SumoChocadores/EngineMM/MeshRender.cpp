#include "stdafx.h"
#include "MeshRender.h"


MeshRender::MeshRender()
{
}

MeshRender::MeshRender(Textura * tex)
{
	/*D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trasl);
	D3DXMatrixIdentity(&rotation);*/
	//texture = tex;
	//defTransMat();
}

void MeshRender::SetMesh(Mesh * mesh)
{
	mesh2 = mesh;
}

Mesh * MeshRender::GetMesh()
{
	return mesh2;
}


MeshRender::~MeshRender()
{
}

void MeshRender::RenderingComposite()
{
	Game* game = Game::getInstance();
	if (texture != NULL)
		game->getDev()->SetTexture(0, texture->GetText());
	else
		game->getDev()->SetTexture(0, NULL);
	//Blending(typeblend, dev);
//	defTransMat();
	game->getDev()->SetFVF(CUSTOMFVF);
	//Multiplicación de Matrices
	//Le digo a la placa que la matriz de mundo es "mat"
	game->getDev()->SetTransform(D3DTS_WORLD, &getTransMat());
	game->getDev()->SetFVF(CUSTOMFVF);
	game->getDev()->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));
	game->getDev()->SetIndices(mesh2->GetInd());
	game->getDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);


	//Especificamos cual VB vamos a usar
	game->getDev()->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));

	//Especificamos indices
	game->getDev()->SetIndices(mesh2->GetInd());

	//dibujamos
	game->getDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	
}
void MeshRender::Blending(int numBlend)
{
	Game* game = Game::getInstance();
	switch (numBlend)
	{
	case 0://Aditivo
		game->getDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		game->getDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
		game->getDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;
	case 1: //Multiplicativo
		game->getDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		game->getDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
		game->getDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
		break;
	case 2://alphaBlending
		game->getDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		game->getDev()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		game->getDev()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;
	default:
		game->getDev()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		break;
	}
}

