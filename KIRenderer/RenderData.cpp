namespace KI
{
namespace Renderer
{
RenderData::RenderData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	SetGeometryData(primitiveType, pVertexBuffer, pIndexBuffer);
}

RenderData::~RenderData()
{
}

void RenderData::SetShaderPass(shared_ptr<IShaderPass> pShaderPass)
{
	m_pShaderPass = pShaderPass;
}

void RenderData::AddRenderRegion(const string& descriptor, shared_ptr<IShaderPass> pShaderPass, int first, int count)
{
	if (GetPrimitiveType() != GL_TRIANGLES)
	{
		assert(0);
		return;
	}
	m_pRenderRegion.push_back(RenderRegion());
	int size = m_pRenderRegion.size() - 1;
	m_pRenderRegion[size].m_descriptor = descriptor;
	m_pRenderRegion[size].m_pShaderPass = pShaderPass;
	m_pRenderRegion[size].m_first = first;
	m_pRenderRegion[size].m_count = count;
}

void RenderData::ClearRenderRegion()
{
	m_pRenderRegion.clear();
}

void RenderData::SetGeometryData(GLuint primitiveType, shared_ptr<IVertexBuffer> pVertexBuffer, shared_ptr<IndexBuffer> pIndexBuffer)
{
	m_pPrimitiveType = primitiveType;
	m_pVertexBuffer = pVertexBuffer;
	m_pIndexBuffer = pIndexBuffer;
}

void RenderData::DrawUseRegion()
{
	// 部分マテリアルで描画
	for (int i = 0; i < m_pRenderRegion.size(); i++)
	{
		DrawInternal(
			m_pRenderRegion[i].m_pShaderPass, 
			m_pRenderRegion[i].m_first,
			m_pRenderRegion[i].m_count);
	}

	// 部分マテリアル以外を通常マテリアルで描画・ソートされている前提
	{
		if (m_pRenderRegion[0].m_first != 0)
		{
			DrawInternal(m_pShaderPass, 0, m_pRenderRegion[0].m_first);
		}

		int first = 0;
		int count = 0;
		for (int i = 0; i < m_pRenderRegion.size() - 1; i++)
		{
			first = m_pRenderRegion[i].m_first + m_pRenderRegion[i].m_count;
			count = m_pRenderRegion[i + 1].m_first - first;

			DrawInternal(m_pShaderPass, first, count);
		}

		int size = m_pRenderRegion.size() - 1;
		first = m_pRenderRegion[size].m_first + m_pRenderRegion[size].m_count;
		count = GetVertexSize() - first;
		if (first != GetVertexSize())
		{
			DrawInternal(m_pShaderPass, first, count);
		}
	}
}

int RenderData::GetVertexSize()
{
	if (m_pIndexBuffer == nullptr)
	{
		return m_pVertexBuffer->GetVertexSize();
	}
	else
	{
		return m_pIndexBuffer->Size();
	}
}
void RenderData::DrawInternal(shared_ptr<IShaderPass> pShaderPass, int first, int count)
{
	if (pShaderPass->NeedReCompileShader())
	{
		pShaderPass->CompileShader(GetVertexBuffer().get());
	}

	auto pShader = pShaderPass->GetShader();
	pShader->Use();
	pShaderPass->Bind();

	if (m_pIndexBuffer == nullptr)
	{
		m_pVertexBuffer->Draw(m_pPrimitiveType, first, count);
	}
	else
	{
		m_pVertexBuffer->DrawByIndexBuffer(m_pPrimitiveType, m_pIndexBuffer.get(), first, count);
	}

	pShaderPass->UnBind();
	pShader->UnUse();
}
void RenderData::Draw()
{
	if (m_pRenderRegion.size() != 0)
	{
		DrawUseRegion();
		return;
	}

	if (m_pVertexBuffer == nullptr ||
		m_pShaderPass == nullptr)
	{
		assert(0);
		return;
	}

	DrawInternal(m_pShaderPass, 0, GetVertexSize());
}

shared_ptr<RenderData> RenderData::Clone()
{
	auto pClone = make_shared<RenderData>();
	pClone->m_pPrimitiveType = m_pPrimitiveType;
	pClone->m_pIndexBuffer	= m_pIndexBuffer;
	pClone->m_pVertexBuffer = m_pVertexBuffer;
	pClone->m_pShaderPass		= m_pShaderPass;

	return pClone;
}
};
}
