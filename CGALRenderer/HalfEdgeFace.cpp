namespace KI
{
HalfEdgeFace::HalfEdgeFace(int index)
{
	m_Index = index;
}

HalfEdgeFace::~HalfEdgeFace()
{
}

void HalfEdgeFace::CalcElement()
{
	m_centroid = CalcCentroid();
	m_area = CalcArea();
	m_normal = CalcNormal();
}

vec3 HalfEdgeFace::CalcNormal()
{
	vec3 v1 = Edge()->Start()->Position();
	vec3 v2 = Edge()->End()->Position();
	vec3 v3 = Edge()->Next()->End()->Position();
	vec3 normal;
	MathHelper::CalcNormal(v1, v2, v3, normal);

	return normalize(normal);
}

float HalfEdgeFace::CalcArea()
{
	float area = 0;
	auto itr = FaceAroundEdgeIterator(this);
	auto before = itr.Current();
	itr.Next();

	for (itr; itr.HasNext(); itr.Next())
	{
		area += MathHelper::CalcTriangleArea(
			before->Start()->Position(),
			before->End()->Position(),
			itr.Current()->End()->Position());
	}

	return area;
}

vec3 HalfEdgeFace::CalcCentroid()
{
	vec3 centroid = vec3(0);
	int m_num = 0;
	for (auto itr = FaceAroundEdgeIterator(this); itr.HasNext(); itr.Next())
	{
		centroid += itr.Current()->End()->Position();
		m_num++;
	}

	float denom = 1.0f / m_num;

	centroid.x *= denom;
	centroid.y *= denom;
	centroid.z *= denom;

	return centroid;
}

bool HalfEdgeFace::Intersection(const vec3& direction, float& distance)
{
	return true;
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
	m_pEdgeItr = m_pFace->Edge();
	m_init = true;
}

bool FaceAroundEdgeIterator::HasNext()
{
	if (m_pEdgeItr == m_pFace->Edge() && m_init == false)
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
	m_pEdgeItr = m_pEdgeItr->Next();
	m_init = false;
}

shared_ptr<HalfEdge> FaceAroundEdgeIterator::Current()
{
	return m_pEdgeItr;
}

}