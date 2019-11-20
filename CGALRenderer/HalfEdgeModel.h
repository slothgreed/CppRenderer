#ifndef HALFEDGE_MODEL_H
#define HALFEDGE_MODEL_H

class HalfEdgeModel : public IModel
{
public:
	HalfEdgeModel();
	~HalfEdgeModel();

	virtual void Load(const std::string& filePath);
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal);
	virtual void GetEdgeList(std::vector<vec3>& edgeList);
	virtual void GetVertexList(std::vector<vec3>& position);
	virtual void GetEdgeIndexList(std::vector<int>& index);
	virtual void GetFaceIndexList(std::vector<int>& index);
	virtual void GetBDB(BDB& bdb);

private:
	void LoadInternal(const string& filePath);
	vector<shared_ptr<HalfEdge>> m_EdgeList;
	vector<shared_ptr<HalfEdgeFace>> m_FaceList;
	vector<shared_ptr<HalfEdgeVertex>> m_VertexList;
};


#endif
