namespace KI 
{
namespace Renderer
{

Scene::Scene()
{
	m_pUniformBuilder = make_unique<UniformBuilder>();
	m_pUniformStruct = m_pUniformBuilder->BuildStruct();
	m_pUniformStruct->SetMaterial(m_pUniformBuilder->BuildMaterial());

}

Scene::~Scene()
{
}

void Scene::Initialize()
{
	m_pUniformStruct->SetScene(m_pUniformBuilder->BuildScene());
	m_pUniformStruct->GetScene()->Generate();

	m_pUniformStruct->SetModel(m_pUniformBuilder->BuildModel());
	m_pUniformStruct->GetModel()->Generate();

	m_pUniformStruct->SetMaterial(m_pUniformBuilder->BuildMaterial());
	m_pUniformStruct->GetMaterial()->Generate();
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
	if (m_pUniformStruct->GetLight() == nullptr)
	{
		m_pUniformStruct->SetLight(m_pUniformBuilder->BuildLight());
		m_pUniformStruct->GetLight()->Generate();
	}
}

void Scene::RemoveLight(shared_ptr<ILight> pLight)
{
}

void Scene::Bind()
{
	m_pUniformStruct->GetScene()->SetViewMatrix(m_pCamera->ViewMatrix());
	m_pUniformStruct->GetScene()->SetProjection(m_pCamera->Projection());
	m_pUniformStruct->GetScene()->Bind();
	m_pUniformStruct->GetModel()->SetViewMatrix(m_pCamera->ViewMatrix());

	BindLight();
}

void Scene::BindLight()
{
	if (m_pLights.size() != 1)
	{
		return;
	}

	LightData light;
	if (m_pLights[0]->Type() == LIGHT_TYPE_DIRECTION)
	{
		DirectionLight* pDirection = (DirectionLight*)m_pLights[0].get();
		light.position = vec4(pDirection->Direction(), 1.0);
		light.ambient = pDirection->Ambient();
		light.diffuse = pDirection->Diffuse();
		light.specular = pDirection->Specular();
	}
	m_pUniformStruct->GetLight()->Set(light);
	m_pUniformStruct->GetLight()->Bind();
}
void Scene::Draw()
{
	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->Draw(m_pUniformStruct);
	}
}

void Scene::FixedShaderDraw(shared_ptr<IShader> pShader, shared_ptr<IShading> pShading)
{
	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		m_pRenderList[i]->FixedShaderDraw(pShader, pShading, m_pUniformStruct);
	}
}

void Scene::UnBind()
{
	if (m_pUniformStruct->GetLight() != nullptr)
	{
		m_pUniformStruct->GetLight()->UnBind();
	}

	m_pUniformStruct->GetScene()->UnBind();
}

shared_ptr<IModelNode> Scene::GetModel(int objectId)
{
	for (int i = 0; i < m_pRenderList.size(); i++)
	{
		if (m_pRenderList[i]->HasPickID(objectId)) {
			return m_pRenderList[i];
		}
	}

	return NULL;
}

bool SceneModelIterator::HasNext()
{
	if (m_pScene->m_pRenderList.size() > m_Index)
	{
		return true;
	}
	else
	{
		return false;
	}
}

IModelNode& SceneModelIterator::Current()
{
	return *(m_pScene->m_pRenderList[m_Index].get());
}

void SceneModelIterator::Next()
{
	m_Index++;
}

VisibleModelIterator::VisibleModelIterator(Scene* pScene)
	: m_pScene(pScene), m_pNextModel(nullptr), m_NextIndex(0)
{
	Next();	// 1î‘ñ⁄ÇÃóvëfÇéÊìæÇµÇƒÇ®Ç≠ÅB
}

bool VisibleModelIterator::HasNext()
{
	if (m_pNextModel == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

IModelNode& VisibleModelIterator::Current()
{
	return *m_pNextModel;
}

void VisibleModelIterator::Next()
{
	bool find = false;
	for (int i = m_NextIndex; i < m_pScene->m_pRenderList.size(); i++)
	{
		if (m_pScene->m_pRenderList[i]->Visible())
		{
			m_pNextModel = m_pScene->m_pRenderList[i].get();
			m_NextIndex = i + 1;
			find = true;
			break;
		}
	}

	if (find == false)
	{
		m_pNextModel = nullptr;
	}

}
}
}


