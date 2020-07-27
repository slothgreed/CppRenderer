
namespace KI
{
PrimitiveNode::PrimitiveNode(shared_ptr<RenderData> pRenderData)
{
	m_name = "Primitive";
	m_pRenderData = pRenderData;
	if (pRenderData->GetShading() == nullptr)
	{
		m_pRenderData->SetShading(make_shared<BasicShading>(vec4(1, 0, 0, 1)));
	}
}

PrimitiveNode::PrimitiveNode(shared_ptr<PrimitiveModel> pPrimitive)
	:IModelNode(pPrimitive)
{
	SetRenderData();
}

PrimitiveNode::PrimitiveNode(shared_ptr<PrimitiveModel> pPrimitive, shared_ptr<IShading> pShading)
	: IModelNode(pPrimitive)
{
	SetRenderData();
	m_pRenderData->SetShading(pShading);
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::DrawCore(shared_ptr<UniformStruct> pUniform)
{
	if (m_pState != nullptr)
	{
		m_pState->Bind();
	}

	m_pRenderData->Draw(pUniform);

	if (m_pState != nullptr)
	{
		m_pState->UnBind();
	}

	Logger::GLError();
}

IndexBuffer* PrimitiveNode::GetIndexBuffer()
{
	if (m_pRenderData == nullptr)
	{
		assert(0);
		return nullptr;
	}

	return m_pRenderData->GetIndexBuffer().get();
}

shared_ptr<DefaultVertexBuffer> PrimitiveNode::GetVertexBuffer()
{
	if (m_pRenderData == nullptr)
	{
		assert(0);
		return nullptr;
	}

	if (m_pRenderData->GetVertexBuffer()->Type() != VERTEX_BUFFER_TYPE_DEFAULT)
	{
		assert(0);
		return nullptr;
	}

	return static_pointer_cast<DefaultVertexBuffer>(m_pRenderData->GetVertexBuffer());
}

void PrimitiveNode::SetRenderData()
{
	m_pRenderData = make_shared<RenderData>();
	auto pPrimitive = static_pointer_cast<PrimitiveModel>(m_pModel);

	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	vector<vec3> position;
	vector<vec3> normal;
	vector<vec2> texcoord;

	pPrimitive->GetFaceList(position, normal, texcoord);
	pVertexBuffer->SetPosition(position);
	if (normal.size() != 0)
	{
		pVertexBuffer->SetNormal(normal);
	}

	if (texcoord.size() != 0)
	{
		pVertexBuffer->SetTexcoord(texcoord);
	}

	vector<int> index;
	pPrimitive->GetFaceIndexList(index);
	shared_ptr<IndexBuffer> pIndexBuffer = nullptr;
	if (index.size() != 0)
	{
		pIndexBuffer = make_shared<IndexBuffer>();
		pIndexBuffer->Set(index);
	}

	m_pRenderData->SetGeometryData(
		GLTypeUtility::PrimType(pPrimitive->GetPrimitive()->GetDrawType()),
		pVertexBuffer, pIndexBuffer);
	m_pRenderData->SetShading(make_shared<BasicShading>(vec4(1, 0, 0, 1)));

}

void PrimitiveNode::AddPartSelect(TOPOLOGY_TYPE type, int first, int count)
{
	auto pShading = ShadingManager::Instance()->GetSystemShading(SYSTEM_SHADING::SYSTEM_SHADING_SELECTION);
	if (type == TOPOLOGY_TYPE::TOPOLOGY_TYPE_FACE)
	{
		if (m_pRenderData->HasRenderRegion())
		{
			m_pRenderData->ClearRenderRegion();
		}

		m_pRenderData->AddRenderRegion("Selection", pShading, first, count);
	}
	else
	{
		assert(0);
	}
}

void PrimitiveNode::Update(void* sender, IEventArgs* args)
{

}

}
