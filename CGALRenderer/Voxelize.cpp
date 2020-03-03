namespace KI
{
Voxelize::Voxelize()
{
}

Voxelize::~Voxelize()
{
	Dispose();
}

void Voxelize::Create(const vector<vec3>& positions, const BDB& bdb, int partition)
{
	m_partition = partition;
	m_bdb = bdb;
	m_length = m_bdb.Max() - m_bdb.Min();
	m_length.x /= m_partition;
	m_length.y /= m_partition;
	m_length.z /= m_partition;

	m_VoxelSpace.resize(partition);
	for (int i = 0; i < partition; i++)
	{
		m_VoxelSpace[i].resize(partition);
		for (int j = 0; j < partition; j++)
		{
			m_VoxelSpace[i][j].resize(partition);
			for (int k = 0; k < partition; k++)
			{
				m_VoxelSpace[i][j][k] = nullptr;
			}
		}
	}

	for (int i = 0; i < positions.size(); i++)
	{
		int x, y, z;
		GetIndex(positions[i], x, y, z);
		vec3 voxelIndex(x, y, z);
		//Logger::Output(KI::LOG_LEVEL::DEBUG, MathHelper::ToString(voxelIndex) + "\n");
		if (m_VoxelSpace[x][y][z] == nullptr)
		{
			m_VoxelSpace[x][y][z] = new Voxel();
		}
	}
}

void Voxelize::GetIndex(const vec3& position, int& i, int& j, int& k)
{
	vec3 voxelPosition = (position - m_bdb.Min());
	i = voxelPosition.x / m_length.x;
	j = voxelPosition.y / m_length.y;
	k = voxelPosition.z / m_length.z;

	if (i >= m_partition)
		i = m_partition - 1;

	if (j >= m_partition)
		j = m_partition - 1;
	
	if (k >= m_partition)
		k = m_partition - 1;

	if (i >= m_partition ||
		j >= m_partition ||
		k >= m_partition)
	{
		assert(0);
	}
}

void Voxelize::GetPosition(int i, int j, int k, vec3& min, vec3& max)
{
	vec3 voxelPosition = m_bdb.Min();
	vec3 cellSize = m_length;
	//cellSize.x /= m_partition;
	//cellSize.y /= m_partition;
	//cellSize.z /= m_partition;

	vec3 position = vec3(i, j, k);
	min = position * cellSize + m_bdb.Min();
	max = (position + vec3(1)) * cellSize + m_bdb.Min();
}

void Voxelize::GetVertexList(vector<vec3>& position, vector<int>& index)
{
	VoxelIterator itr = VoxelIterator(m_VoxelSpace, m_partition);
	int counter = 0;
	int counter2 = 0;
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
		cube.SetIndexOffset(counter * 8);
		cube.Build(min, max);
		position.insert(position.end(), cube.Position().begin(), cube.Position().end());
		index.insert(index.end(), cube.Index().begin(), cube.Index().end());
		counter++;
	}
}

void Voxelize::Dispose()
{
	for (int i = 0; i < m_VoxelSpace.size(); i++)
	{
		for (int j = 0; j < m_VoxelSpace[i].size(); j++)
		{
			for (int k = 0; k < m_VoxelSpace[i][j].size(); k++)
			{
				delete m_VoxelSpace[i][j][k];
			}
		}
	}
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
	return m_VoxelSpace[m_Index.x][m_Index.y][m_Index.z];
}
}