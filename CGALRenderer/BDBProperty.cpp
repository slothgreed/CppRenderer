namespace KI
{
BDBProperty::BDBProperty(BDB& bdb)
{
	m_bdb = bdb;
	GenVBO();
}

BDBProperty::~BDBProperty()
{
}

void BDBProperty::GenVBO()
{
	m_pVertexBuffer = make_shared<DefaultVertexBuffer>();
	m_pVertexBuffer->Generate(VERTEX_LAYOUT::VERTEX_LAYOUT_P);

	vector<vec3> position;
	position.push_back(m_bdb.Min());
	position.push_back(vec3(m_bdb.Max().x, m_bdb.Min().y, m_bdb.Min().z));
	position.push_back(vec3(m_bdb.Max().x, m_bdb.Max().y, m_bdb.Min().z));
	position.push_back(vec3(m_bdb.Min().x, m_bdb.Max().y, m_bdb.Min().z));

	position.push_back(vec3(m_bdb.Min().x, m_bdb.Min().y, m_bdb.Max().z));
	position.push_back(vec3(m_bdb.Max().x, m_bdb.Min().y, m_bdb.Max().z));
	position.push_back(m_bdb.Max());
	position.push_back(vec3(m_bdb.Min().x, m_bdb.Max().y, m_bdb.Max().z));

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

	m_pVertexBuffer->SetPosition(GL_LINES, position);
	m_pVertexBuffer->SetIndex(index);

	ShaderBuildInfo buildInfo;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT_P, buildInfo);
	m_pShader = ShaderManager::Instance()->FindOrNew(buildInfo);
}

void BDBProperty::Draw()
{
	m_pShader->Use();
	m_pVertexBuffer->Draw();
	m_pShader->UnUse();
}
}
