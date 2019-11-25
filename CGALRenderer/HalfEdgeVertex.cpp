#include "HalfEdgeVertex.h"
namespace KI
{

HalfEdgeVertex::HalfEdgeVertex(int index)
{
	m_Index = index;
}

HalfEdgeVertex::~HalfEdgeVertex()
{
}
void HalfEdgeVertex::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
}

void HalfEdgeVertex::CalcElement()
{
	m_normal = CalcNormal();
	m_area = CalcArea();
}

float HalfEdgeVertex::CalcArea()
{
	float area = 0;
	auto itr = VertexAroundEdgeIterator(this);
	HalfEdge* before = itr.Current();
	itr.Next();

	for (itr; itr.HasNext(); itr.Next())
	{
		area = MathHelper::CalcTriangleArea(
			before->Start()->Position(),
			before->End()->Position(),
			itr.Current()->End()->Position());
		area++;
	}

	return area;
}

vec3 HalfEdgeVertex::CalcNormal()
{
	HalfEdgeFace* face;
	vec3 sum = vec3(0);
	int num = 0;
	for (auto itr = VertexAroundEdgeIterator(this); itr.HasNext(); itr.Next())
	{
		face = itr.Current()->Face().get();
		sum += face->Normal();
		num++;
	}

	double denom = 1.0f / num;
	vec3 normal;
	normal.x = sum.x * denom;
	normal.y = sum.y * denom;
	normal.z = sum.z * denom;

	return normal;
}

string HalfEdgeVertex::ToString()
{
	string str;
	str += "(this, x, y, z) :";
	str += "(";
	str += to_string(Index())	   + ", ";
	str += to_string(m_position.x) + ", ";
	str += to_string(m_position.y) + ", ";
	str += to_string(m_position.z) + ", ";
	str += ")";

	return str;
}

VertexAroundEdgeIterator::VertexAroundEdgeIterator(HalfEdgeVertex* pVertex)
{
	m_pVertex = pVertex;
	m_pEdgeItr = m_pVertex->Edge().get();
	m_init = true;

}

bool VertexAroundEdgeIterator::HasNext()
{
	if (m_pEdgeItr == m_pVertex->Edge().get() && m_init == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void VertexAroundEdgeIterator::Next()
{
	m_pEdgeItr = m_pEdgeItr->Opposite()->Next().get();
	m_init = false;
}

HalfEdge* VertexAroundEdgeIterator::Current()
{
	return m_pEdgeItr;
}
}