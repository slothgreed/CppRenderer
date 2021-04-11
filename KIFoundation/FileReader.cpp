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

void* FileReader::ReadBinary(Format format)
{
	assert(m_fileStream.is_open());
	void* data = nullptr;
	switch (format)
	{
	case KI::Foundation::Format::FLOAT:
		m_fileStream.read((char*)&data, sizeof(float));
		break;
	case KI::Foundation::Format::VEC2:
		m_fileStream.read((char*)&data, sizeof(vec2));
		break;
	case KI::Foundation::Format::VEC3:
		m_fileStream.read((char*)&data, sizeof(vec3));
		break;
	case KI::Foundation::Format::VEC4:
		m_fileStream.read((char*)&data, sizeof(vec4));
		break;
	default:
		assert(0);
		break;
	}

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