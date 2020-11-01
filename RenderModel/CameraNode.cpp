namespace KI
{
namespace RenderModel
{
CameraNode::CameraNode(shared_ptr<ICamera> pCamera)
{
	m_pCamera = pCamera;
	m_pCamera->AddObserver(this);
	SetRenderData();
}

CameraNode::~CameraNode()
{
	m_pCamera->RemoveObserver(this);
}

void CameraNode::SetRenderData()
{
	//auto pShading = make_shared<VertexShading>(VERTEX_SHADING_COLOR);
	//auto pRenderData = make_shared<RenderData>();


	//m_pVertexBuffer = make_shared<DefaultVertexBuffer>();
	//vector<vec3> position;
	//position.push_back(m_pCamera->Center());
	//position.push_back(m_pCamera->XDirection());
	//position.push_back(m_pCamera->Center());
	//position.push_back(m_pCamera->YDirection());
	//position.push_back(m_pCamera->Center());
	//position.push_back(m_pCamera->ZDirection());
	//vector<vec3> color;
	//color.push_back(vec3(1, 0, 0));
	//color.push_back(vec3(1, 0, 0));
	//color.push_back(vec3(0, 1, 0));
	//color.push_back(vec3(0, 1, 0));
	//color.push_back(vec3(0, 0, 1));
	//color.push_back(vec3(0, 0, 1));

	//m_pVertexBuffer->SetPosition(position);
	//m_pVertexBuffer->SetColor(color);

	//pRenderData->SetShading(pShading);
	//pRenderData->SetGeometryData(PRIM_TYPE::PRIM_TYPE_LINES, m_pVertexBuffer);
	//AddRenderData(0, pRenderData);
}

void CameraNode::Update(void* sender, IEventArgs* args)
{
	//auto pRenderData = GetRenderData(0);
	//assert(pRenderData != NULL);

	//vector<vec3> position;
	//position.push_back(m_pCamera->Eye());
	//position.push_back(m_pCamera->XDirection());
	//position.push_back(m_pCamera->Eye());
	//position.push_back(m_pCamera->YDirection());
	//position.push_back(m_pCamera->Eye());
	//position.push_back(m_pCamera->ZDirection());

	//m_pVertexBuffer->SetPosition(position);
}
}
}
