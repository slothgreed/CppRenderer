namespace KI
{
HalfEdge::HalfEdge(int index)
{
	m_Index = index;
}

HalfEdge::~HalfEdge()
{
}

void HalfEdge::Set(
	shared_ptr<HalfEdgeVertex> end,
	shared_ptr<HalfEdge> next,
	shared_ptr<HalfEdge> before, 
	shared_ptr<HalfEdge> opposite,
	shared_ptr<HalfEdgeFace> face)
{
	m_End = end;
	m_Next = next;
	m_Before = before;
	m_Opposite = opposite;
	m_Face = face;
}

void HalfEdge::SetBefore(shared_ptr<HalfEdge> edge)
{
	m_Before = edge;
}

void HalfEdge::SetNext(shared_ptr<HalfEdge> edge)
{
	m_Next = edge;
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
	str += "(this, End, Next, Before, Opposite, Face) :";
	str += "(";
	str += to_string(Index())				+ ", ";
	str += to_string(m_End->Index())		+ ", ";
	str += to_string(m_Next->Index())		+ ", ";
	str += to_string(m_Before->Index())		+ ", ";
	str += to_string(m_Opposite->Index())	+ ", ";
	str += to_string(m_Face->Index());
	str += ")";

	return str;
}

}