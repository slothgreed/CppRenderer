namespace KI
{
Voxelize::Voxelize()
{
	m_pVoxelSpace = nullptr;
}

Voxelize::~Voxelize()
{
	Dispose();
}

void Voxelize::Create(const vector<vec3>& positions, const vec3& origin, int partition)
{
	m_pVoxelSpace = new Voxel***[partition];
	m_partition = partition;
	m_origin = origin;
	for (int i = 0; i < partition; i++)
	{
		m_pVoxelSpace[i] = new Voxel**[partition];
		for (int j = 0; j < partition; j++)
		{
			m_pVoxelSpace[i][j] = new Voxel*[partition];
			for (int k = 0; k < partition; k++)
			{
				m_pVoxelSpace[i][j][k] = nullptr;
			}
		}
	}

	for (int i = 0; i < positions.size(); i++)
	{
		int x, y, z;
		GetIndex(positions[i], x, y, z);
		if (m_pVoxelSpace[x][y][z] == nullptr)
		{
			m_pVoxelSpace[x][y][z] = new Voxel();
		}
	}
}

void Voxelize::GetIndex(const vec3& position, int& i, int& j, int& k)
{
	vec3 voxelPosition = (position - m_origin);
	i = voxelPosition.x / m_partition;
	j = voxelPosition.y / m_partition;
	k = voxelPosition.z / m_partition;
}
void Voxelize::GetPosition(int i, int j, int k, vec3& min, vec3& max)
{

}

void Voxelize::GetVertexList(vector<vec3>& position, vector<int>& index)
{
	VoxelIterator itr = VoxelIterator(m_pVoxelSpace, m_partition);
	int counter = 0;
	Cube cube;
	for (; itr.HasNext(); itr.Next())
	{
		vec3 voxelIndex = itr.CurrentIndex();
		if (itr.Current() == nullptr)
		{
			continue;
		}

		vec3 min;
		vec3 max;
		GetPosition(voxelIndex.x, voxelIndex.y, voxelIndex.z, min, max);
		cube.SetIndexOffset(counter * 36);
		cube.Build(min, max);
		position.insert(position.end(), cube.Position().begin(), cube.Position().end());
		index.insert(index.end(), cube.Index().begin(), cube.Index().end());
	}
}

void Voxelize::Dispose()
{
	if (m_pVoxelSpace == nullptr)
	{
		return;
	}

	for (int i = 0; i < m_partition; i++) 
	{
		for (int j = 0; j < m_partition; j++)
		{
			for (int k = 0; k < m_partition; k++)
			{
				delete m_pVoxelSpace[i][j][k];
			}

			delete[] m_pVoxelSpace[i][j];
		}

		delete[] m_pVoxelSpace[i];
	}

	delete[] m_pVoxelSpace;
}


bool VoxelIterator::HasNext()
{
	if (m_Index.x == m_partition - 1 &&
		m_Index.y == m_partition - 1 &&
		m_Index.z == m_partition - 1)
	{
		return false;
	}

	return true;
}

ivec3 VoxelIterator::CurrentIndex()
{
	return m_Index;
}
void VoxelIterator::Next()
{
	m_Index.x++;
	if (m_Index.x == m_partition)
	{
		m_Index.x = 0;
		m_Index.y++;
	}

	if (m_Index.y == m_partition)
	{
		m_Index.y = 0;
		m_Index.z++;
	}
}

Voxel* VoxelIterator::Current()
{
	return m_pVoxelSpace[m_Index.x][m_Index.y][m_Index.z];
}
}