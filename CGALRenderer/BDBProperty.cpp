namespace KI
{
BDBProperty::BDBProperty()
{
}

BDBProperty::~BDBProperty()
{
}

void BDBProperty::Build(IModelNode* pModelNode)
{
	auto pVertexBuffer = make_shared<DefaultVertexBuffer>();
	
	vector<vec3> position;
	BDB bdb;
	pModelNode->GetModel()->GetBDB(bdb);
	GetBDBPosition(bdb, position);
	pVertexBuffer->SetPosition(position);

	vector<int> index;
	index.resize(24);
	int i = 0;
	// front
	index[i] = 0; i++; index[i] = 1; i++;
	index[i] = 1; i++; index[i] = 2; i++;
	index[i] = 2; i++; index[i] = 3; i++;
	index[i] = 3; i++; index[i] = 0; i++;

	// back
	index[i] = 4; i++; index[i] = 5; i++;
	index[i] = 5; i++; index[i] = 6; i++;
	index[i] = 6; i++; index[i] = 7; i++;
	index[i] = 7; i++; index[i] = 4; i++;
	
	// depth
	index[i] = 0; i++; index[i] = 4; i++;
	index[i] = 1; i++; index[i] = 5; i++;
	index[i] = 2; i++; index[i] = 6; i++;
	index[i] = 3; i++; index[i] = 7;

	auto pIndexBuffer = make_shared<IndexBuffer>();
	pIndexBuffer->Set(index);

	m_pRenderData = make_shared<RenderData>(PRIM_TYPE_LINES, pVertexBuffer, pIndexBuffer);
	m_pRenderData->SetShading(make_shared<BasicShading>(vec4(0, 0, 0, 1)));
}

void BDBProperty::GetBDBPosition(const BDB& bdb, vector<vec3>& position)
{
	position.resize(8);
	position[0] = bdb.Min();
	position[1] = vec3(bdb.Max().x, bdb.Min().y, bdb.Min().z);
	position[2] = vec3(bdb.Max().x, bdb.Max().y, bdb.Min().z);
	position[3] = vec3(bdb.Min().x, bdb.Max().y, bdb.Min().z);
			  
	position[4] = vec3(bdb.Min().x, bdb.Min().y, bdb.Max().z);
	position[5] = vec3(bdb.Max().x, bdb.Min().y, bdb.Max().z);
	position[6] = bdb.Max();
	position[7] = vec3(bdb.Min().x, bdb.Max().y, bdb.Max().z);
}
void BDBProperty::Update(IModelNode* pModelNode)
{
	vector<vec3> position;
	BDB bdb;
	pModelNode->GetModel()->GetBDB(bdb);
	GetBDBPosition(bdb, position);
	auto pVertexBuffer = m_pRenderData->GetVertexBuffer();
	if (pVertexBuffer->Type() == VERTEX_BUFFER_TYPE_DEFAULT)
	{
		auto pDefaultBuffer = static_pointer_cast<DefaultVertexBuffer>(pVertexBuffer);
		pDefaultBuffer->SetPosition(position);
	}
	else
	{
		assert(0);
	}
}

void BDBProperty::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderData->Draw(pUniform);
}
}
