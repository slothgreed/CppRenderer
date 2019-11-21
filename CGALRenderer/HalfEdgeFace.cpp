namespace KI
{
HalfEdgeFace::HalfEdgeFace(int index)
{
	m_Index = index;
}

HalfEdgeFace::~HalfEdgeFace()
{
}

vec3 HalfEdgeFace::Normal()
{
	return vec3(1, 0, 0);
}

string HalfEdgeFace::ToString()
{
	string str;
	str += "(this) :";
	str += "(";
	str += to_string(Index()) ;
	str += ")";

	return str;
}

FaceAroundEdgeIterator::FaceAroundEdgeIterator(HalfEdgeFace* pFace)
{
	m_pFace = pFace;
	m_pEdgeItr = m_pFace->Edge().get();
	m_init = true;
}

bool FaceAroundEdgeIterator::HasNext()
{
	if (m_pEdgeItr == m_pFace->Edge().get() && m_init == false)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void FaceAroundEdgeIterator::Next()
{
	m_pEdgeItr = m_pEdgeItr->Next().get();
	m_init = false;
}

HalfEdge* FaceAroundEdgeIterator::Current()
{
	return m_pEdgeItr;
}
}