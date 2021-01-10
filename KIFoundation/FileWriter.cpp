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

bool FileWriter::Open(const std::string& filePath)
{
	//if (FileUtility::IsExist(filePath))
	//{
	//	return false;
	//}

	m_fileStream.open(filePath.data(), std::ios::out);
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

void FileWriter::Close()
{
	if (m_fileStream.is_open()) {
		m_fileStream.close();
	}
}
}
}