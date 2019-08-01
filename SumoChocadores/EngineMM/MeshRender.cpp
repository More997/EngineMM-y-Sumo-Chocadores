#include "stdafx.h"
#include "MeshRender.h"
#include "stdafx.h"
#include <d3d9.h> //Busca el header de directx en los path
#pragma comment (lib, "d3d9.lib") //Incluyo la lib a mi proyecto
#include <d3dx9.h>
#pragma comment (lib, "d3dx9.lib")

MeshRender::MeshRender(): draw(false)
{
}

MeshRender::MeshRender(Textura * tex) : draw(false)
{
	texture = tex;
}
MeshRender::MeshRender(Camera * _cam)
{
	cam = _cam;
	model = 0;
}
MeshRender::MeshRender(Mesh * comingMesh, Camera * _cam)
{
	cam = _cam;
	model = 0;
	mesh2 = comingMesh;
}
MeshRender::MeshRender(Textura * tex, Camera * _cam)
{
	texture = tex;
	cam = _cam;
}
MeshRender::MeshRender(Mesh* _mesh, Textura * tex, Camera * _cam)
{
	cam = _cam;
	model = 0;
	mesh2 = _mesh;
	texture = tex;
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

void MeshRender::defTransMat()
{
	Composite::defTransMat();
}

void MeshRender::RenderingComposite()
{
	draw = inFrustum();
	if (draw)
	{
		Game* game = Game::getInstance();
		
		game->getDev()->SetTransform(D3DTS_WORLD, &getTransMat());
		game->getDev()->SetFVF(CUSTOMFVF);
		game->getDev()->SetStreamSource(0, mesh2->GetVb(), 0, sizeof(Vertex));
		game->getDev()->SetIndices(mesh2->GetInd());
		if (texture != NULL)
			game->getDev()->SetTexture(0, texture->GetText());
		else
			game->getDev()->SetTexture(0, NULL);
		game->getDev()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, mesh2->vertexes.size(), 0, mesh2->indexes.size() / 3); //3D
	}
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

BoundingBox MeshRender::GetMeshBB()
{
	return mesh2->GetBB();
}

void MeshRender::setCamera(Camera * _cam)
{
	cam = _cam;
}

bool MeshRender::inFrustum()
{
	Game *game = Game::getInstance();
	vector<D3DXPLANE> m_Frustrum = cam->BuildViewFrustum();
	BoundingBox bb = GetBoundingBox();
	for (int i = 0; i < 6; i++) 
	{
		
		if (((m_Frustrum[i].a * bb.xMin) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) < 0) &&
			((m_Frustrum[i].a * bb.xMax) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) < 0) &&
			((m_Frustrum[i].a * bb.xMax) + (m_Frustrum[i].b * bb.yMax) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) < 0) &&
			((m_Frustrum[i].a * bb.xMax) + (m_Frustrum[i].b * bb.yMax) + (m_Frustrum[i].c * bb.zMax) + (m_Frustrum[i].d) < 0) &&
			((m_Frustrum[i].a * bb.xMin) + (m_Frustrum[i].b * bb.yMax) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) < 0) &&
			((m_Frustrum[i].a * bb.xMin) + (m_Frustrum[i].b * bb.yMax) + (m_Frustrum[i].c * bb.zMax) + (m_Frustrum[i].d) < 0) &&			
			((m_Frustrum[i].a * bb.xMin) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMax) + (m_Frustrum[i].d) < 0) &&
			((m_Frustrum[i].a * bb.xMax) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMax) + (m_Frustrum[i].d) < 0))
		{
			game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 102, 0, 0), 1.0f, 0);
			return false;
		}
		/*
		if ((m_Frustrum[i].a * bb.xMin) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) >= 0)
		{
			game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 102, 0, 0), 1.0f, 0);
			return true;
		}
		if ((m_Frustrum[i].a * bb.xMax) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) >= 0)
		{
			game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 102, 0, 0), 1.0f, 0);
			return true;
		}
		if ((m_Frustrum[i].a * bb.xMax) + (m_Frustrum[i].b * bb.yMax) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) >= 0)
		{
			game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 102, 0, 0), 1.0f, 0);
			return true;
		}
		if ((m_Frustrum[i].a * bb.xMin) + (m_Frustrum[i].b * bb.yMax) + (m_Frustrum[i].c * bb.zMin) + (m_Frustrum[i].d) >= 0)
		{
			game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 102, 0, 0), 1.0f, 0);
			return true;
		}
		if ((m_Frustrum[i].a * bb.xMin) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMax) + (m_Frustrum[i].d) >= 0)
		{
			game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 102, 0, 0), 1.0f, 0);
			return true;
		}
		if
			((m_Frustrum[i].a * bb.xMax) + (m_Frustrum[i].b * bb.yMin) + (m_Frustrum[i].c * bb.zMax) + (m_Frustrum[i].d) >= 0)
		{
			game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 102, 0, 0), 1.0f, 0);
			cout << "no esta en camara" << endl;
			return true;
		}
		*/
	}
	
	game->getDev()->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_ARGB(0, 0, 102, 0), 1.0f, 0);
	return true;
	}



