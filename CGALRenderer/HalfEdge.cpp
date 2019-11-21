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