
Workspace::Workspace()
{
	
}

Workspace::~Workspace()
{
	RELEASE_INSTANCE(m_pDefaultShader);
	RELEASE_INSTANCE(m_pAxis);
	RELEASE_INSTANCE(m_pShaderScene);
}

void Workspace::Initialize(Project* m_pProject)
{
	m_pDefaultShader = new Shader();
	m_pDefaultShader->BuildFromFile(
		m_pProject->ProjectDir() + "\\Resource\\version.txt",
		m_pProject->ProjectDir() + "\\Resource\\default.vert",
		m_pProject->ProjectDir() + "\\Resource\\default.frag");
	
	m_pCamera = make_shared<Camera>();
	m_pCamera->LookAt(vec3(0, 0, -2), vec3(0, 0, 0), vec3(0, 1, 0));
	m_pCamera->Perspective(glm::radians(60.0f), 1, 0.01, 100);

	m_pShaderScene = new ShaderScene();
	m_pShaderScene->Generate();
	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	sceneData.color = vec4(1, 0, 1, 1);
	m_pShaderScene->Set(sceneData);
	m_pShaderScene->Block(m_pDefaultShader->Program());

	m_pPolyhedron = new CGALPolyhedron();
	m_pPolyhedron->Load("E:\\Tools\\CGAL-5.0-beta1\\build\\examples\\Polygon_mesh_processing\\Debug\\data\\blobby.off");
	//m_pPolyhedron->Load("E:\\Tools\\CGAL-5.0-beta1\\build\\examples\\Polygon_mesh_processing\\Debug\\data\\eight.off");
	//m_pPolyhedron->Load("E:\\cgModel\\model\\fandisk\\fandisk.off");
	m_pPolyhedron->BuildDrawData();

	std::vector<vec3> position;
	position.reserve(6);
	position.push_back(vec3(0.0, -0.5, 0.0));
	position.push_back(vec3(0.0, 0.5, 0.0));
	position.push_back(vec3(-0.5, 0.0, 0.0));
	position.push_back(vec3(0.5, 0.0, 0.0));
	//position.push_back(vec3(0.0, 0.0, -1));
	//position.push_back(vec3(0.0, 0.0, 1));
	m_pAxis = new VertexBuffer(VERTEX_LAYOUT_P);
	m_pAxis->Generate();
	m_pAxis->GenerateVAO();
	m_pAxis->SetPosition(GL_LINES, position);
}

void Workspace::Invoke()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	m_pDefaultShader->Use();

	SceneData sceneData;
	sceneData.ViewMatrix = m_pCamera->ViewMatrix();
	sceneData.Projection = m_pCamera->Projection();
	sceneData.color = vec4(1, 0, 1, 1);
	m_pShaderScene->Set(sceneData);
	m_pShaderScene->Use();

	m_pAxis->Draw();
	
	m_pPolyhedron->Draw();

	m_pDefaultShader->UnUse();

}