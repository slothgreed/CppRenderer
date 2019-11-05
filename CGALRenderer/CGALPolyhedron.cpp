#include <CGAL/normal_vector_newell_3.h>

#include <fstream>
CGALPolyhedron::CGALPolyhedron()
	: CGALModel()
{
}

CGALPolyhedron::~CGALPolyhedron()
{
	RELEASE_INSTANCE(m_model);
}

void CGALPolyhedron::Load(const string& filePath)
{
	ifstream input(filePath);

	m_model = new Polyhedron();
	
	input >> (*m_model);

	//m_halfEdge = &m_model->make_tetrahedron();

	//if (m_model->is_tetrahedron(*m_halfEdge))
	//{
	//	Logger::Output(LOG_LEVEL::ERROR, "Failed Load CGALPolyhedron");
	//}

}

void CGALPolyhedron::GetFacetList(vector<vec3>& facetList, vector<vec3>& normalList)
{
	for (Polyhedron::Facet_const_iterator facet = m_model->facets_begin();
		facet != m_model->facets_end(); facet++)
	{
		if (facet != boost::graph_traits<Polyhedron>::null_face())
		{
			BuildFacet(facet, facetList, normalList);
		}
	}
}

void CGALPolyhedron::GetEdgeList(vector<vec3>& edgeList)
{
	for (Polyhedron::Halfedge_const_iterator edge = m_model->halfedges_begin();
		edge != m_model->halfedges_end(); edge++)
	{
		if (edge < edge->opposite())
		{
			BuildEdge(edge, edgeList);
		}
	}
}

void CGALPolyhedron::GetVertexList(vector<vec3>& vertex)
{
	for (Polyhedron::Vertex_const_iterator vertex = m_model->vertices_begin();
		vertex != m_model->vertices_end(); vertex++)
	{
		BuildVertex(vertex);
	}
}

void CGALPolyhedron::BuildFacet(const Facet_const_handle& facet, vector<vec3>& position, vector<vec3> & normal)
{
	CGAL::Color color = CGAL::Color(255, 0, 0);
	
	Halfedge_const_handle halfEdge = facet->facet_begin();
	if (halfEdge == NULL)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Can't read data");
		return;
	}

	do
	{
		auto point = halfEdge->vertex()->point();
		Local_Vector norm = CalculateVertexNormal(halfEdge);
		position.push_back(vec3(point.x(), point.y(), point.z()));
		normal.push_back(vec3(norm.x(), norm.y(), norm.z()));

		halfEdge = halfEdge->next();
	} while (halfEdge != facet->facet_begin());


}

CGALPolyhedron::Local_Vector CGALPolyhedron::CalculateFaceNormal(const Halfedge_const_handle& halfEdge)
{
	Local_Vector normal = CGAL::NULL_VECTOR;
	Halfedge_const_handle itr = halfEdge;
	Halfedge_const_handle end = halfEdge;
	unsigned int count = 0;

	do
	{
		CGAL::newell_single_step_3
		(
			itr->vertex()->point(),
			itr->next()->vertex()->point(),
			normal
		);


		count++;
		itr = itr->next();
	} while (end != itr);

	return Local_Kernel::Construct_scaled_vector_3()(normal, 1.0 / count);
}

CGALPolyhedron::Local_Vector CGALPolyhedron::CalculateVertexNormal(const Halfedge_const_handle& halfEdge)
{
	Local_Vector normal = CGAL::NULL_VECTOR;
	Halfedge_const_handle itr = halfEdge;
	Halfedge_const_handle end = halfEdge;
	unsigned int count = 0;

	do
	{
		if (!itr->is_border())
		{
			Local_Vector faceNormal = CalculateFaceNormal(itr);
			normal = Local_Kernel::Construct_sum_of_vectors_3()(normal, faceNormal);
		}

		itr = itr->next()->opposite();

	} while (itr != end);

	if (!Local_Kernel::Equal_3()(normal, CGAL::NULL_VECTOR))
	{
		normal = Local_Kernel::Construct_scaled_vector_3()
			(normal, 1.0 / CGAL::sqrt(normal.squared_length()));
	}

	return normal;
}

void CGALPolyhedron::BuildEdge(const Halfedge_const_handle& edge, vector<vec3>& position)
{
	CGAL::Point_3<Kernel>  p1 = edge->vertex()->point();
	CGAL::Point_3<Kernel>  p2 = edge->opposite()->vertex()->point();
	position.push_back(vec3(p1.x(), p1.y(), p1.z()));
	position.push_back(vec3(p2.x(), p2.y(), p2.z()));
}

void CGALPolyhedron::BuildVertex(const Vertex_const_handle& vertex)
{
	CGAL::Point_3<Kernel> p1 = vertex->point();
}
