namespace KI
{
namespace Foundation
{
FileReader::FileReader()
{
}

FileReader::~FileReader()
{
	Close();
}

bool FileReader::Open(const std::string& filePath, bool binary)
{
	//if (FileUtility::IsExist(filePath))
	//{
	//	return false;
	//}

	if (binary) {
		m_fileStream.open(filePath.data(), std::ios::in | ios::binary);
	}
	else {
		m_fileStream.open(filePath.data(), std::ios::in);
	}
	return true;
}

bool FileReader::ReadLine(std::string& contents, bool endl)
{
	if (getline(m_fileStream, contents)) {
		return true;
	}
	else {
		return false;
	}
}

float FileReader::ReadFloat()
{
	assert(m_fileStream.is_open());
	float data = 0;
	m_fileStream.read((char*)&data, sizeof(float));
	return data;
}
vec2 FileReader::ReadVec2()
{
	assert(m_fileStream.is_open());
	vec2 data;
	m_fileStream.read((char*)&data, sizeof(vec2));
	return data;
}
vec3 FileReader::ReadVec3()
{
	assert(m_fileStream.is_open());
	vec3 data;
	m_fileStream.read((char*)&data, sizeof(vec3));
	return data;
}
vec4 FileReader::ReadVec4()
{
	assert(m_fileStream.is_open());
	vec4 data;
	m_fileStream.read((char*)&data, sizeof(vec4));
	return data;
}


bool FileReader::EndOfFile()
{
	return m_fileStream.eof();
}
void FileReader::Close()
{
	if (m_fileStream.is_open()) {
		m_fileStream.close();
	}
}
}
}