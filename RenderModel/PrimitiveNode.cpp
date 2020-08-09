namespace KI
{
namespace RenderModel
{
PrimitiveNode::PrimitiveNode(shared_ptr<RenderData> pRenderData)
{
	m_name = "Primitive";
	AddRenderData(0, pRenderData);
	if (pRenderData->GetShading() == nullptr)
	{
		pRenderData->SetShading(make_shared<BasicShading>(vec4(1, 0, 0, 1)));
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
	GetRenderData(0)->SetShading(pShading);
}

PrimitiveNode::~PrimitiveNode()
{
}

void PrimitiveNode::PreDraw(shared_ptr<UniformStruct> pUniform, int index)
{
	if (m_pState != nullptr)
	{
		m_pState->Bind();
	}

	Logger::GLError();
}

void PrimitiveNode::PostDraw(shared_ptr<UniformStruct> pUniform, int index)
{
	if (m_pState != nullptr)
	{
		m_pState->UnBind();
	}

	Logger::GLError();
}

IndexBuffer* PrimitiveNode::GetIndexBuffer()
{
	return GetRenderData(0)->GetIndexBuffer().get();
}

shared_ptr<DefaultVertexBuffer> PrimitiveNode::GetVertexBuffer()
{
	if (GetRenderData(0)->GetVertexBuffer()->Type() != VERTEX_BUFFER_TYPE_DEFAULT)
	{
		assert(0);
		return nullptr;
	}

	return static_pointer_cast<DefaultVertexBuffer>(GetRenderData(0)->GetVertexBuffer());
}

void PrimitiveNode::SetRenderData()
{
	auto pRenderData = make_shared<RenderData>();
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

	pRenderData->SetGeometryData(
		GLTypeUtility::PrimType(pPrimitive->GetPrimitive()->GetDrawType()),
		pVertexBuffer, pIndexBuffer);
	pRenderData->SetShading(make_shared<BasicShading>(vec4(1, 0, 0, 1)));

	AddRenderData(0, pRenderData);
}

void PrimitiveNode::AddPartSelect(TOPOLOGY_TYPE type, int first, int count)
{
	auto pShading = ShadingManager::Instance()->GetSystemShading(SYSTEM_SHADING::SYSTEM_SHADING_SELECTION);
	if (type == TOPOLOGY_TYPE::TOPOLOGY_TYPE_FACE)
	{
		if (GetRenderData(0)->HasRenderRegion())
		{
			GetRenderData(0)->ClearRenderRegion();
		}

		GetRenderData(0)->AddRenderRegion("Selection", pShading, first, count);
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
}
