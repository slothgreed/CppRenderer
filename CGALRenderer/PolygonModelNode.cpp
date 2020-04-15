namespace KI
{
PolygonModelNode::PolygonModelNode(shared_ptr<IModel> model)
	: IModelNode(model)
{
	m_name = "PolygonModelNode";
	SetRenderData();
	VisibleBDB(true);
	VisibleNormal(true);
}

PolygonModelNode::~PolygonModelNode()
{
}

void PolygonModelNode::Draw()
{
	if (m_pFaceMaterial != NULL && m_pFaceData != NULL)
	{
		m_pFaceMaterial->Draw(m_pFaceData.get());
	}

	if (m_pEdgeMaterial != NULL && m_pEdgeData != NULL)
	{
		m_pEdgeMaterial->Draw(m_pEdgeData.get());
	}

	DrawProperty();

}

void PolygonModelNode::ShowProperty()
{
	//ImGui::Begin(m_name.data());
	//ImGui::Text(m_bdb.ToString().data());
	//ImGui::End();
}

IPolygonModel* PolygonModelNode::GetModel()
{
	if (IPolygonModel::IsPolygonModel(m_pModel->Type()))
	{
		return (IPolygonModel*)(m_pModel.get());
	}
	else
	{
		assert(0);
		return nullptr;
	}
}

void PolygonModelNode::VisibleBDB(bool visibility)
{
	GetModel()->GetBDB(m_bdb);
	AddProperty(make_shared<BDBProperty>());
}

shared_ptr<IVertexBuffer> PolygonModelNode::GetVertexBuffer()
{
	if (m_pFaceData == nullptr)
	{
		assert(0);
		return nullptr;
	}

	return m_pFaceData->GetVertexBuffer(); 
}

void PolygonModelNode::VisibleNormal(bool visibility)
{
	if (GetModel()->HasVertexList())
	{
		AddProperty(make_shared<NormalProperty>());
	}
	else
	{
		Logger::Output(LOG_LEVEL::DEBUG, "don't have vertex list");
	}
}

void PolygonModelNode::SetRenderData()
{
	if (GetModel()->HasVertexList() == false)
	{
		vector<vec3> facet;
		vector<vec3> normal;
		GetModel()->GetFacetList(facet, normal);
		auto pFaceBuffer = make_shared<DefaultVertexBuffer>();
		pFaceBuffer->SetPosition(facet);
		pFaceBuffer->SetNormal(normal);
		m_pFaceMaterial = make_shared<DefaultMaterial>();
		m_pFaceData = make_shared <RenderData>(GL_TRIANGLES, pFaceBuffer);

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		m_pEdgeMaterial = make_shared<DefaultMaterial>();
		m_pEdgeData = make_shared <RenderData>(GL_LINES, pEdgeBuffer);

	}
	else
	{
		vector<Vertex> vertex;
		vector<int> index;
		GetModel()->GetVertexList(vertex);
		GetModel()->GetFaceIndexList(index);
		auto pFaceBuffer = make_shared<DefaultVertexBuffer>();

		vector<vec3> position;
		vector<vec3> normal;
		for (int i = 0; i < vertex.size(); i++)
		{
			position.push_back(vertex[i].Position());
			normal.push_back(vertex[i].Normal());
		}

		pFaceBuffer->SetPosition(position);
		pFaceBuffer->SetNormal(normal);
		m_pFaceMaterial = make_shared<DefaultMaterial>();
		
		auto pFaceIndex = make_shared <IndexBuffer>();
		pFaceIndex->Set(index);
		m_pFaceData = make_shared <RenderData>(GL_TRIANGLES, pFaceBuffer, pFaceIndex);

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		auto pEdgeMaterial = make_shared<DefaultMaterial>();
		pEdgeMaterial->SetFixColor(vec4(0));
		m_pEdgeMaterial = pEdgeMaterial;
		m_pEdgeData = make_shared <RenderData>(GL_LINES, pEdgeBuffer);

	}

}

void PolygonModelNode::VisibleFace(bool visibility)
{

}

void PolygonModelNode::VisibleEdge(bool visibility)
{

}

void PolygonModelNode::Update(void* sender, IEventArgs* args)
{
	SetRenderData();

	IModelNode::Update(sender, args);
}

void PolygonModelNode::SetPickID(int startIndex, int& endIndex)
{
	if (m_pFaceData->GetIndexBuffer() != nullptr)
	{
		int pickIndex = startIndex;
		vector<int> pickId;
		pickId.resize(m_pFaceData->GetIndexBuffer()->Size());
		for (int i = 0; i < pickId.size(); i+=3){
			pickId[i] = pickIndex;
			pickId[i + 1] = pickIndex + 1;
			pickId[i + 2] = pickIndex + 2;
			pickIndex += 3;
		}

		assert(0);
	}
}

}