#include "stdafx.h"
#include "MeshRenderer.h"
#include "Vertex.h"
#include "Model.h"
#include "Transform.h"



MeshRenderer::MeshRenderer(Model* _model, Material* _material)
{
	m_Model = _model;
	m_Material = _material;
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::DibujarMesh(LPDIRECT3DDEVICE9 dev)
{
	Transform *transform = GetParent()->GetComponent<Transform>();

	m_Material->SetBlend(dev, m_Material->getBlend());
	m_Material->setWrap(dev, m_Material->getWrap());
	m_Material->setFiltro(dev, m_Material->getFiltro());

	dev->SetTexture(0, m_Material->textura);

	if (m_Material->GetShader())
	{
		UINT passes;
		m_Material->GetShader()->Begin(&passes, 0);
		for (int i = 0; i < passes; i++)
		{
			m_Material->GetShader()->BeginPass(i);
			dev->SetFVF(MYFVF);
			dev->SetIndices(m_Model->GetIndexBuffer());
			dev->SetStreamSource(0, m_Model->GetVertexBuffer(), 0, sizeof(Vertex));
			dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_Model->vertexes.size(), 0, m_Model->indexes.size() / 3);
			dev->SetTransform(D3DTS_WORLD, &transform->GetWorldMatrix());
			m_Material->GetShader()->EndPass();
		}
		m_Material->GetShader()->End();
	}
	else
	{
		dev->SetFVF(MYFVF);
		dev->SetStreamSource(0, m_Model->GetVertexBuffer(), 0, sizeof(Vertex));
		dev->SetIndices(m_Model->GetIndexBuffer());
		dev->SetTransform(D3DTS_WORLD, &transform->GetWorldMatrix());
		dev->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_Model->vertexes.size(), 0, m_Model->indexes.size() / 3);
	}
}

void MeshRenderer::UpdateComposite()
{
}

