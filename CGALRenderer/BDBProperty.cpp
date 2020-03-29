namespace KI
{
BDBProperty::BDBProperty()
{
}

BDBProperty::~BDBProperty()
{
}

void BDBProperty::Build(IModel* pModel)
{
	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();

	
	vector<vec3> position;
	BDB bdb;
	pModel->GetBDB(bdb);
	GetBDBPosition(bdb, position);
	m_pVertexBuffer->SetPosition(GL_LINES, position);

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

	m_pIndexBuffer = make_shared<IndexBuffer>();
	m_pIndexBuffer->Set(GL_LINES, index);

	auto pBuildInfo = make_shared<IShaderBuildInfo>(SHADER_TYPE_DEFAULT);
	auto pVertexCode = make_shared<DefaultVertexCode>();
	pVertexCode->SetShaderDefine(m_pVertexBuffer->Layout());
	pBuildInfo->SetVertexCode(pVertexCode);
	pBuildInfo->SetFragCode(make_shared<DefaultFragCode>());
	m_pShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);

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
void BDBProperty::Update(IModel* pModel)
{
	vector<vec3> position;
	BDB bdb;
	pModel->GetBDB(bdb);
	GetBDBPosition(bdb, position);
	m_pVertexBuffer->SetPosition(GL_LINES, position);
}

void BDBProperty::Draw()
{
	m_pShader->Use();
	m_pVertexBuffer->Draw(m_pIndexBuffer.get());
	m_pShader->UnUse();
}
}
