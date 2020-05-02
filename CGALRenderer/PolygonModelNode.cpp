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
	if (m_pFaceData != NULL)
	{
		m_pFaceData->Draw();
	}

	if (m_pEdgeData != NULL)
	{
		m_pEdgeData->Draw();
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
		m_pFaceData = make_shared <RenderData>(GL_TRIANGLES, pFaceBuffer);
		m_pFaceData->SetMaterial(make_shared<DefaultMaterial>());

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		m_pEdgeData = make_shared <RenderData>(GL_LINES, pEdgeBuffer);
		m_pEdgeData->SetMaterial(make_shared<DefaultMaterial>());

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
		
		auto pFaceIndex = make_shared <IndexBuffer>();
		pFaceIndex->Set(index);
		m_pFaceData = make_shared <RenderData>(GL_TRIANGLES, pFaceBuffer, pFaceIndex);
		m_pFaceData->SetMaterial(make_shared<DefaultMaterial>());

		vector<vec3> edge;
		GetModel()->GetEdgeList(edge);
		auto pEdgeBuffer = make_shared<DefaultVertexBuffer>();
		pEdgeBuffer->SetPosition(edge);

		auto pEdgeMaterial = make_shared<DefaultMaterial>();
		pEdgeMaterial->SetFixColor(vec4(0, 1, 0, 1));
		m_pEdgeData = make_shared <RenderData>(GL_LINES, pEdgeBuffer);
		m_pEdgeData->SetMaterial(pEdgeMaterial);

		auto pSelectionMaterial = make_shared<DefaultMaterial>();
		pSelectionMaterial->SetFixColor(vec4(1, 0, 0, 1));
		m_pFaceData->AddRenderRegion("Test", pSelectionMaterial, 3, 270);
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

void PolygonModelNode::CalculatePickID(int startIndex, int& nextStartIndex)
{
	int nodeStartIndex = startIndex;
	if (m_pFaceData->GetIndexBuffer() != nullptr)
	{
		vector<vec3> pickId;
		IGLPick::CalculateID(
			m_pFaceData->GetPrimitiveType(),
			m_pFaceData->GetVertexBuffer()->GetVertexSize(),
			nodeStartIndex, nextStartIndex,
			pickId);

		BuildPickData(m_pFaceData->GetPrimitiveType(), m_pFaceData, pickId);

		nodeStartIndex = nextStartIndex;
	}

	if (m_pEdgeData->GetIndexBuffer() != nullptr)
	{
		int pickIndex = startIndex;
		vector<vec3> pickId;
		IGLPick::CalculateID(
			m_pEdgeData->GetPrimitiveType(),
			m_pFaceData->GetVertexBuffer()->GetVertexSize(),
			nodeStartIndex, nextStartIndex,
			pickId);

		BuildPickData(m_pEdgeData->GetPrimitiveType(), m_pEdgeData, pickId);

		nodeStartIndex = nextStartIndex;
	}
}

void PolygonModelNode::PickDraw()
{
	if (m_pFaceData != NULL)
	{
		auto pRenderData = GetPickRenderData(m_pFaceData->GetPrimitiveType());
		pRenderData->Draw();
	}

	if (m_pEdgeData != NULL)
	{
		//auto pRenderData = GetPickRenderData(m_pEdgeData->GetPrimitiveType());
		//pRenderData->Draw();
	}
}

}