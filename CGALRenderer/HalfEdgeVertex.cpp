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