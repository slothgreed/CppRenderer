namespace KI
{

class Voxel
{
};

class VoxelIterator : public IIterator<Voxel*>
{
public:
	VoxelIterator(Voxel**** voxelSpace, int partition)
		: m_pVoxelSpace(voxelSpace), m_partition(partition), m_Index(0) {};
	~VoxelIterator() {};

	virtual bool HasNext() override;
	virtual Voxel* Current() override;
	virtual ivec3 CurrentIndex();
	virtual void Next() override;
private:
	int m_partition;
	ivec3 m_Index;
	Voxel**** m_pVoxelSpace;
};

class Voxelize
{
public:
	Voxelize();
	~Voxelize();
	void Create(const vector<vec3>& positions, const vec3& origin, int partition);
	void GetVertexList(vector<vec3>& position, vector<int>& index);
private:
	void GetIndex(const vec3& position, int& i, int& j, int& k);
	void GetPosition(int i, int j, int k, vec3& min, vec3& max);
	void Dispose();
	int m_partition;
	vec3 m_origin;
	Voxel**** m_pVoxelSpace; // ‚RŽŸŒ³”z—ñ
};

}