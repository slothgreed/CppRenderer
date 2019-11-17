#ifndef CGAL_MODEL_H
#define CGAL_MODEL_H
class CGALModel : public IModel
{
public:
	CGALModel();
	~CGALModel();

	virtual void Load(const std::string& filePath) = 0;
	virtual void GenSampleModel() = 0;
	virtual void GetFacetList(std::vector<vec3>& position, std::vector<vec3>& normal) = 0;
	virtual void GetEdgeList(std::vector<vec3>& edgeList) = 0;
	virtual void GetVertexList(std::vector<vec3>& position) = 0;
	virtual void GetBDB(BDB& bdb) = 0;
protected:
	void SetBDB(BDB bdb);
private:
	BDB m_bdb;
};

#endif CGAL_MODEL_H