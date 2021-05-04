namespace KI
{

namespace Topology
{
HalfEdgeParameterIO::HalfEdgeParameterIO()
{

}
HalfEdgeParameterIO::~HalfEdgeParameterIO()
{

}

void HalfEdgeParameterIO::OutputTangent(const std::string& filePath, const vector<vec3>& tangents)
{
	FileWriter writer;
	writer.Open(filePath,true);

	for (int i = 0; i < tangents.size(); i++) {
		float x = tangents[i].x;
		float y = tangents[i].y;
		float z = tangents[i].z;
		writer.WriteBinary(&x,Format::FLOAT);
		writer.WriteBinary(&y, Format::FLOAT);
		writer.WriteBinary(&z, Format::FLOAT);
	}

	writer.Close();
}


void HalfEdgeParameterIO::LoadTangent(const std::string& filePath, vector<vec3>* tangents)
{
	FileReader reader;
	reader.Open(filePath, true);
	float x, y, z;
	int count = 0;

	while (!reader.EndOfFile())
	{
		if (!reader.EndOfFile()) {
			(*tangents).push_back(reader.ReadVec3());
		}
	}

	reader.Close();

}

}

}
