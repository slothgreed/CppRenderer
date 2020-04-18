#include "DefaultVertexBuffer.h"
namespace KI
{
namespace Renderer
{

void PickInfo::Set(shared_ptr<RenderData> pRenderData, const vector<vec3>& pPickInfo)
{
	m_pRenderData = pRenderData;
	m_pPickInfo = pPickInfo;
}

void IPickable::CalculateID(
	GLuint primitiveType,
	int indexNum,
	int startIndex, 
	int &nextStartIndex, vector<vec3>& ids)
{
	ids.resize(indexNum);
	int counter = 0;
	if (primitiveType == GL_TRIANGLES)
	{
		for (int i = 0; i < indexNum; i += 3)
		{
			vec3 color = IndexToColor(startIndex + counter);
			ids[i]	   = color;
			ids[i + 1] = color;
			ids[i + 2] = color;
			counter++;
			Logger::Output(LOG_LEVEL::DEBUG, MathHelper::ToString(color) + "\n");
		}
	}
	else if (primitiveType == GL_LINES)
	{
		for (int i = 0; i < indexNum; i += 2)
		{
			vec3 color = IndexToColor(startIndex + counter);
			ids[i]		= color;
			ids[i + 1]  = color;
			counter++;
		}
	}
	else if (primitiveType == GL_POINTS)
	{
		int counter = 0;
		for (int i = 0; i < indexNum; i++)
		{
			ids[i]		= IndexToColor(startIndex + counter);
			counter++;
		}
	}

	nextStartIndex = startIndex + counter;
}

vec3 IPickable::IndexToColor(int index)
{
	vec3 color;
	color.r = (float)((index & 0x000000FF) >> 0) / 255.0f;
	color.g = (float)((index & 0x0000FF00) >> 8) / 255.0f;
	color.b = (float)((index & 0x00FF0000) >> 16) / 255.0f;
	return color;
}

void IPickable::BuildPickData(int key, shared_ptr<RenderData> pRenderData, const vector<vec3>& ids)
{
	m_pPickInfo[key] = PickInfo();

	auto pPickData = make_shared<RenderData>();
	auto pDefaultBuffer = make_shared<DefaultVertexBuffer>();
	pDefaultBuffer->SetArrayBuffer(VERTEX_ATTRIB_POSITION,
		pRenderData->GetVertexBuffer()->GetArrayBuffer(VERTEX_ATTRIB_POSITION));
	pDefaultBuffer->SetColor(ids);
	pDefaultBuffer->SetVertexSize(pRenderData->GetVertexBuffer()->GetVertexSize());



	pPickData->Set(pRenderData->GetPrimitiveType(),	pDefaultBuffer, pRenderData->GetIndexBuffer());

	m_pPickInfo[key].Set(pPickData, ids);
}

shared_ptr<RenderData> IPickable::GetPickRenderData(int key)
{
	return m_pPickInfo[key].GetRenderData();
}
}
}