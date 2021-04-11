namespace KI
{
namespace Foundation
{
FileWriter::FileWriter()
{
}

FileWriter::~FileWriter()
{
	Close();
}

bool FileWriter::Open(const std::string& filePath, bool binary)
{
	//if (FileUtility::IsExist(filePath))
	//{
	//	return false;
	//}

	if (binary) {
		m_fileStream.open(filePath.data(), std::ios::out | ios::binary);
	}
	else {
		m_fileStream.open(filePath.data(), std::ios::out);
	}
	return true;
}

void FileWriter::Write(const std::string& contents, bool endl)
{
	assert(m_fileStream.is_open());
	m_fileStream << contents.data();
	if (endl) {
		m_fileStream << std::endl;
	}
}

void FileWriter::WriteBinary(void* contents, Format format, bool endl)
{
	assert(m_fileStream.is_open());
	switch (format)
	{
	case KI::Foundation::Format::FLOAT:
		m_fileStream.write((char*)contents, sizeof(float));
		break;
	case KI::Foundation::Format::VEC2:
		m_fileStream.write((char*)contents, sizeof(vec2));
		break;
	case KI::Foundation::Format::VEC3:
		m_fileStream.write((char*)contents, sizeof(vec3));
		break;
	case KI::Foundation::Format::VEC4:
		m_fileStream.write((char*)contents, sizeof(vec4));
		break;
	default:
		assert(0);
		break;
	}

}


void FileWriter::Close()
{
	if (m_fileStream.is_open()) {
		m_fileStream.close();
	}
}
}
}