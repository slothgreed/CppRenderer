namespace KI {
namespace Renderer
{

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	m_pUniformScene = make_shared<UniformScene>();
	m_pUniformScene->Generate();

}

void Scene::AddModelNode(shared_ptr<IModelNode> pModelNode)
{
	m_pRenderList.push_back(pModelNode);
}

void Scene::RemoveModelNode(shared_ptr<IModelNode> pModelNode)
{

}

void Scene::AddLight(shared_ptr<ILight> pLight)
{
	m_pLights.push_back(pLight);
	if (m_pUniformLight == nullptr)
	{
		m_pUniformLight = make_shared<UniformLight>();
		m_pUniformLight->Generate();
	}
}

void Scene::RemoveLight(shared_ptr<ILight> pLight)
{
}

void Scene::Bind()
{
	SceneData sceneData;
	sceneData.viewMatrix = m_pCamera->ViewMatrix();
	sceneData.projection = m_pCamera->Projection();
	m_pUniformScene->Set(sceneData);
	m_pUniformScene->Bind();

	if (m_pLights.size() != 0)
	{
		for (int i = 0; i < m_pLights.size(); i++)
		{
			m_pUniformLight->Set(m_pLights[i].get());
		}
		m_pUniformLight->Bind();
	}
}
void Scene::Draw()
{
	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->Draw();
	}
}

void Scene::UnBind()
{
	if (m_pUniformLight != nullptr)
	{
		m_pUniformLight->UnBind();
	}

	m_pUniformScene->UnBind();
}

}
}


