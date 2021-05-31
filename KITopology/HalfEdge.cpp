namespace KI
{
namespace Topology
{
HalfEdge::HalfEdge(int index)
{
	m_Index = index;
}

HalfEdge::~HalfEdge()
{
}

void HalfEdge::Set(
	HalfEdgeVertex* end,
	HalfEdge* next,
	HalfEdge* before, 
	HalfEdge* opposite,
	HalfEdgeFace* face)
{
	m_End = end;
	m_Next = next;
	m_Before = before;
	m_Opposite = opposite;
	m_Face = face;
}

void HalfEdge::SetEnd(HalfEdgeVertex* vertex)
{
	m_End = vertex;
}

void HalfEdge::SetBefore(HalfEdge* edge)
{
	m_Before = edge;
}

void HalfEdge::SetNext(HalfEdge* edge)
{
	m_Next = edge;
}

void HalfEdge::SetOpposite(HalfEdge* edge)
{
	m_Opposite = edge;
}

void HalfEdge::SetFace(HalfEdgeFace* face)
{
	m_Face = face;
}

void HalfEdge::Validate()
{
	assert(m_End != NULL);
	assert(m_Next != NULL);
	assert(m_Before != NULL);
	assert(m_Opposite != NULL);
	assert(m_Face != NULL);
	
	assert(m_Opposite->Opposite() == this);
	assert(m_Opposite->End() == Start());
	assert(m_Opposite->Start() == End());

	assert(m_Next->Before() == this);
	assert(m_Next->Start() == m_End); 
	assert(m_Next->Face() == m_Face);

	assert(m_Before->Next() == this);
	assert(m_Before->End() == Start());
	assert(m_Before->Face() == m_Face);
}

void HalfEdge::CalcElement()
{
	m_angle = CalcAngle();
	m_length = CalcLength();
}

float HalfEdge::CalcAngle()
{
	auto before = Before()->Opposite();
	float angle = MathHelper::CalcRadian(
		Start()->Position() - End()->Position(),
		before->End()->Position() - End()->Position()
	);

	return angle;
}

float HalfEdge::CalcLength()
{
	return length(Start()->Position() - End()->Position());
}

string HalfEdge::ToString()
{
	string str;
	str += "(this, Start, End, Next, Before, Opposite, Face) :";
	str += "(";
	str += to_string(Index())				+ ", ";
	str += to_string(Start()->Index())		+ ", ";
	str += to_string(m_End->Index())		+ ", ";
	str += to_string(m_Next->Index())		+ ", ";
	str += to_string(m_Before->Index())		+ ", ";
	str += to_string(m_Opposite->Index())	+ ", ";
	str += to_string(m_Face->Index());
	str += ")";

	return str;
}
}
}