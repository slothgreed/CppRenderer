#include "IModelNode.h"
namespace KI
{
namespace Renderer
{

PropertyIterator::PropertyIterator(IModelNode* pNode)
{
	m_pNode = pNode;
	m_index = 0;
}

bool PropertyIterator::HasNext() 
{
	if (m_pNode->m_pProperty.size() == 0) {
		return false;
	}

	if (m_index >= m_pNode->m_pProperty.size()) {
		return false;
	}

	return true;
}

void PropertyIterator::Next()
{
	m_index++;
}


IModelProperty* PropertyIterator::Current()
{
	return m_pNode->m_pProperty[m_index].get();
}


IModelNode::IModelNode()
	:m_ModelMatrix(mat4x4(1.0)),
	m_visible(true)
{
}
IModelNode::IModelNode(shared_ptr<IModel> model)
	: IModelNode()
{
	m_pModel = model;
	m_pModel->AddObserver(this);
}

IModelNode::~IModelNode()
{
	if (m_pModel != nullptr)
	{
		m_pModel->RemoveObserver(this);
	}
}


void IModelNode::AddProperty(shared_ptr<IModelProperty> prop, IPropertyArgs* propArgs)
{
	if (!HasProperty(prop->Type()))
	{
		prop->Build(this, propArgs);
		m_pProperty.push_back(prop);
	}
}

shared_ptr<IModelProperty> IModelNode::GetProperty(unsigned int type)
{
	auto itr = std::find_if(m_pProperty.begin(), m_pProperty.end(),
		[type](shared_ptr<IModelProperty> value) {return value->Type() == type; });
	if (itr == m_pProperty.end())
	{
		return nullptr;
	}

	return *itr;
}

bool IModelNode::HasProperty(unsigned int type)
{
	auto itr = std::find_if(m_pProperty.begin(), m_pProperty.end(),
		[type](shared_ptr<IModelProperty> value) {return value->Type() == type; });
	if (itr == m_pProperty.end())
	{
		return false;
	}

	return true;
}

void IModelNode::RemoveProperty(shared_ptr<IModelProperty> prop)
{
	auto itr = std::find_if(m_pProperty.begin(), m_pProperty.end(),
		[&prop](shared_ptr<IModelProperty> value) {return value->Type() == prop->Type(); });
	if (itr != m_pProperty.end())
	{
		size_t dist = std::distance(m_pProperty.begin(), itr);
		m_pProperty.erase(m_pProperty.begin() + dist);
	}
}


void IModelNode::BindModel(shared_ptr<UniformStruct> pUniform, int index)
{
	if (pUniform != NULL)
	{
		if (pUniform->GetModel() != NULL)
		{
			pUniform->GetModel()->SetModelMatrix(m_ModelMatrix);
			pUniform->GetModel()->SetObjectId(m_pRenderData[index].pRenderData->GetPickID());
			pUniform->GetModel()->Bind();
		}
	}
}

void IModelNode::UnBindModel(shared_ptr<UniformStruct> pUniform, int index)
{
	if (pUniform != NULL)
	{
		if (pUniform->GetModel() != NULL)
		{
			pUniform->GetModel()->UnBind();
		}
	}
}

void IModelNode::FixedShaderDraw(shared_ptr<IShader> pShader, shared_ptr<IShading> pShading, shared_ptr<UniformStruct> pUniform)
{
	if (m_visible == false)
	{
		return;
	}
	else
	{
		for (int i = 0; i < m_pRenderData.size(); i++)
		{
			if (m_pRenderData[i].visible == false ||
				m_pRenderData[i].pRenderData == nullptr) {
				continue;
			}

			BindModel(pUniform, i);
			PreDraw(pUniform, i);
			m_pRenderData[i].pRenderData->Draw(pShader, pShading, pUniform);
			PostDraw(pUniform, i);
		}

		UnBindModel(pUniform, 0);

		DrawProperty(pUniform);
	}
}

void IModelNode::Draw(shared_ptr<UniformStruct> pUniform)
{
	if (m_visible == false)
	{
		return;
	}
	else
	{
		for (int i = 0; i < m_pRenderData.size(); i++)
		{
			if (m_pRenderData[i].visible == false ||
				m_pRenderData[i].pRenderData == nullptr) {
				continue;
			}

			BindModel(pUniform, i);
			PreDraw(pUniform, i);
			m_pRenderData[i].pRenderData->Draw(pUniform);
			PostDraw(pUniform, i);
		}

		UnBindModel(pUniform, 0);
	}

	DrawProperty(pUniform);
}

void IModelNode::SetVisible(int id, bool visible)
{
	m_pRenderData[id].visible = visible;
}
bool IModelNode::Visible(int id)
{
	return m_pRenderData[id].visible;
}

void IModelNode::AddRenderData(int id, shared_ptr<RenderData> pRenderData)
{
	m_pRenderData[id] = RenderDataInfo(pRenderData);
}

void IModelNode::RemoveRenderData(int id, shared_ptr<RenderData> pRenderData)
{
	assert(0);
}

shared_ptr<RenderData> IModelNode::GetRenderData(int id)
{
	if (m_pRenderData[id].pRenderData == NULL) {
		assert(0);
		return nullptr;
	}

	return m_pRenderData[id].pRenderData;
}

void IModelNode::DrawProperty(shared_ptr<UniformStruct> pUniform)
{
	for (int i = 0; i < m_pProperty.size(); i++)
	{
		if (!m_pProperty[i]->Visible()) {
			continue;
		}

		m_pProperty[i]->Draw(pUniform);
	}
}

void IModelNode::AddSelect(PICK_TYPE type, shared_ptr<IShading> pShader, int index, int first, int count)
{
	if (type == TOPOLOGY_TYPE::TOPOLOGY_TYPE_FACE)
	{
		if (GetRenderData(index)->HasRenderRegion())
		{
			GetRenderData(index)->ClearRenderRegion();
		}

		GetRenderData(index)->AddRenderRegion("Selection", pShader, first, count);
	}
	else
	{
		assert(0);
	}
}


void IModelNode::Update(void* sender, IEventArgs* args)
{
	UpdateProperty(sender, args);
}

void IModelNode::UpdateProperty(void* sender, IEventArgs* args)
{
	for (int i = 0; i < m_pProperty.size(); i++)
	{
		m_pProperty[i]->Update(sender, args);
	}
}

void IModelNode::AddPickID(int start, int* next)
{
	for (int i = 0; i < m_pRenderData.size(); i++)
	{
		m_pRenderData[i].pRenderData->SetPickID(start);
		start++;
	}

	*next = start;
}

bool IModelNode::HasPickID(int id)
{
	for (int i = 0; i < m_pRenderData.size(); i++)
	{
		if (m_pRenderData[i].pRenderData->GetPickID() == id)
		{
			return true;
		}
	}

	return false;
}
}
}