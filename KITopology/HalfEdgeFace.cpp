namespace KI
{
namespace Topology
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
	vec3 v1, v2, v3;
	vec3 normal;
	GetVertex(&v1, &v2, &v3);

	MathHelper::CalcNormal(v1, v2, v3, normal);

	return normalize(normal);
}

float HalfEdgeFace::CalcArea()
{
	float area = 0;
	auto itr = FaceAroundEdgeIterator(this);
	auto before = (HalfEdge*)itr.Current();
	itr.Next();

	for (itr; itr.HasNext(); itr.Next())
	{
		HalfEdge* current = (HalfEdge*)itr.Current();
		area += MathHelper::CalcTriangleArea(
			before->Start()->Position(),
			before->End()->Position(),
			current->End()->Position());
	}

	return area;
}

vec3 HalfEdgeFace::CalcCentroid()
{
	vec3 centroid = vec3(0);
	int m_num = 0;
	for (auto itr = FaceAroundEdgeIterator(this); itr.HasNext(); itr.Next())
	{
		centroid += ((HalfEdge*)itr.Current())->End()->Position();
		m_num++;
	}

	float denom = 1.0f / m_num;

	centroid.x *= denom;
	centroid.y *= denom;
	centroid.z *= denom;

	return centroid;
}

void HalfEdgeFace::Validate()
{
	assert(m_Edge != NULL);
	assert(m_Edge->Face() == this);
	assert(CalcVertexNum() == 3);
}

void HalfEdgeFace::GetVertex(vec3* v1, vec3* v2, vec3* v3)
{
	*v1 = Edge()->Start()->Position();
	*v2 = Edge()->End()->Position();
	*v3 = Edge()->Next()->End()->Position();
}

int HalfEdgeFace::CalcVertexNum()
{
	int counter = 0;
	for (auto itr = FaceAroundEdgeIterator(this); itr.HasNext(); itr.Next())
	{
		counter++;
	}
	
	return counter;
}

bool HalfEdgeFace::Intersection(const Ray& ray, vec3& position, float& distance)
{
	if (CalcVertexNum() != 3)
	{
		assert(0);
		return false;
	}

	bool result = Intersect::RayToTriangle(
		ray,
		m_Edge->End()->Position(),
		m_Edge->Start()->Position(),
		m_Edge->Before()->Start()->Position(),
		position, distance);


	return result;
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

HalfEdge* FaceAroundEdgeIterator::Current()
{
	return m_pEdgeItr;
}
}
}