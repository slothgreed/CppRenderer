namespace KI
{

class Voxel
{
};

class VoxelIterator : public IIterator<Voxel*>
{
public:
	VoxelIterator(vector<vector<vector<Voxel*>>>& voxelSpace, int partition)
		: m_VoxelSpace(voxelSpace), m_partition(partition), m_Index(0) {};
	~VoxelIterator() {};

	virtual bool HasNext() override;
	virtual Voxel* Current() override;
	virtual ivec3 CurrentIndex();
	virtual void Next() override;
private:
	int m_partition;
	ivec3 m_Index;
	vector<vector<vector<Voxel*>>> m_VoxelSpace;
};

class Voxelize
{
public:
	Voxelize();
	~Voxelize();
	void Create(const vector<vec3>& positions, const BDB& bdb, int partition);
	void GetVertexList(vector<vec3>& position, vector<int>& index);
private:
	void GetIndex(const vec3& position, int& i, int& j, int& k);
	void GetPosition(int i, int j, int k, vec3& min, vec3& max);
	void Dispose();
	int m_partition;
	BDB m_bdb;
	vec3 m_length;
	vector<vector<vector<Voxel*>>> m_VoxelSpace;
};

}