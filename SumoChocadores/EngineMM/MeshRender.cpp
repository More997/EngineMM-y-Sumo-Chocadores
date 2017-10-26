#include "stdafx.h"
#include "MeshRender.h"
#include "stdafx.h"
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

MeshRender::MeshRender()
{
}

MeshRender::MeshRender(Textura * tex)
{
	/*D3DXMatrixIdentity(&scale);
	D3DXMatrixIdentity(&trasl);
	D3DXMatrixIdentity(&rotation);*/
	texture = tex;
	//defTransMat();
}
void MeshRender::SetTexture(Textura * tex)
{
	texture = tex;
}

Textura * MeshRender::GetTexture()
{
	return texture;
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
	//game->getDev()->SetFVF(CUSTOMFVF);
	game->getDev()->SetIndices(mesh2->GetInd());
	game->getDev()->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));
	game->getDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh2->vertexes.size(), 0, mesh2->indexes.size() / 3); //3D
	//game->getDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2); //2D


	//Especificamos cual VB vamos a usar
/*	game->getDev()->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));

	//Especificamos indices
	game->getDev()->SetIndices(mesh2->GetInd());

	//dibujamos
	game->getDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	*/
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

void MeshRender::Warping(int numWarp)
{
	Game *game = Game::getInstance();
	switch (numWarp)
	{
	default:
		break;
	case 1:
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		break;
	case 2:
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_BORDER);
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_BORDER);
		break;
	case 3:
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
		break;
	case 4:
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_FORCE_DWORD);
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_FORCE_DWORD);
		break;
	case 5:
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);
		break;
	case 6:
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRRORONCE);
		game->getDev()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRRORONCE);
		break;

	}
}
void MeshRender::Filtro(int numfiltro)
{
	Game* game = Game::getInstance();
		switch (numfiltro)
		{
		case 1:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_ANISOTROPIC);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC);
			break;
		case 2:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_CONVOLUTIONMONO);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_CONVOLUTIONMONO);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_CONVOLUTIONMONO);
			break;
		case 3:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_FORCE_DWORD);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_FORCE_DWORD);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_FORCE_DWORD);
			break;
		case 4:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_GAUSSIANQUAD);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_GAUSSIANQUAD);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_GAUSSIANQUAD);
			break;
		case 5:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
			break;
		case 6:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);
			break;
		case 7:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_PYRAMIDALQUAD);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_PYRAMIDALQUAD);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_PYRAMIDALQUAD);
			break;

		default:
			game->getDev()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
			game->getDev()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_NONE);
			game->getDev()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
			break;
		}
}

