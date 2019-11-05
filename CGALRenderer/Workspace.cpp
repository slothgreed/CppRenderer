
Workspace::Workspace()
{
	
}

Workspace::~Workspace()
{
}

void Workspace::Initialize(Project* m_pProject)
{
	ShaderUtility::SetShaderDirectory(m_pProject->ProjectDir() + "\\Resource");
	m_pDefaultShader = make_shared<DefaultShader>();
	string vertexDefine;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PC, vertexDefine);

	ShaderBuildInfo buildInfo;
	buildInfo.vertexDefine	= vertexDefine;
		
	m_pDefaultShader->Build(buildInfo);
	
	m_pCamera = make_shared<Camera>();
	m_pCamera->LookAt(vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 1, 0));
	m_pCamera->Perspective(glm::radians(60.0f), 1, 0.01, 100);

	m_pUniformScene = make_shared<UniformScene>();
	m_pUniformScene->Generate();
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);

	shared_ptr<CGALPolyhedron> polyhedron = make_shared<CGALPolyhedron>();
	polyhedron->Load("E:\\Tools\\CGAL-5.0-beta1\\build\\examples\\Polygon_mesh_processing\\Debug\\data\\blobby.off");
	//m_pPolyhedron->Load("E:\\Tools\\CGAL-5.0-beta1\\build\\examples\\Polygon_mesh_processing\\Debug\\data\\eight.off");
	//m_pPolyhedron->Load("E:\\cgModel\\model\\fandisk\\fandisk.off");

	vector<vec3> facet;
	vector<vec3> normal;
	polyhedron->GetFacetList(facet, normal);
	auto facetBuffer = make_shared<VertexBuffer>();
	facetBuffer->Generate(VERTEX_LAYOUT_PN);
	facetBuffer->SetPosition(GL_TRIANGLES, facet);
	facetBuffer->SetNormal(normal);

	ShaderBuildInfo facetShaderInfo;
	string facetVertexDefine;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PN, facetVertexDefine);
	facetShaderInfo.vertexDefine = facetVertexDefine;
	auto facetShader = make_shared<DefaultShader>();
	facetShader->Build(facetShaderInfo);

	auto facetNode = make_shared<RenderNode>(facetShader, facetBuffer);
	m_pRenderList.push_back(facetNode);

	vector<vec3> edge;
	polyhedron->GetEdgeList(edge);
	auto edgeBuffer = make_shared<VertexBuffer>();
	edgeBuffer->Generate(VERTEX_LAYOUT_P);
	edgeBuffer->SetPosition(GL_LINES, edge);
	
	ShaderBuildInfo edgeShaderInfo;
	string edgeVertexDefine;
	DefaultShader::GetVertexShaderDefine(VERTEX_LAYOUT::VERTEX_LAYOUT_PN, edgeVertexDefine);
	edgeShaderInfo.vertexDefine = facetVertexDefine;
	shared_ptr<IShader> edgeShader = make_shared<DefaultShader>();
	edgeShader->Build(edgeShaderInfo);

	auto edgeNode = make_shared<RenderNode>(edgeShader, edgeBuffer);
	m_pRenderList.push_back(edgeNode);

	auto axis = make_shared<VertexBuffer>();
	ModelGenerator::Axis(axis.get());
	auto axisNode = make_shared<RenderNode>(m_pDefaultShader, axis);
	m_pRenderList.push_back(axisNode);

}

void Workspace::Invoke()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);
	m_pUniformScene->Bind();

	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->Draw();
	}
	
	m_pUniformScene->UnBind();
}