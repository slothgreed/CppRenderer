namespace KI
{
namespace Foundation
{
FileUtility::FileUtility()
{
}

FileUtility::~FileUtility()
{
}

bool FileUtility::Load(const std::string& filePath, std::string& contents)
{
	std::ifstream ifs(filePath);
	std::string line;
	if (ifs.fail())
	{
		Logger::Output(LOG_LEVEL::ERROR, "file open error");
		return false;
	}

	while ((getline(ifs, line)))
	{
		contents += line + "\n";
	}

	return true;
}

void FileUtility::GetExtension(const std::string& filePath, std::string& ext)
{
	int index = (int)filePath.find_last_of(".");
	ext = filePath.substr(index, filePath.size() - index);
}

bool FileUtility::CheckExtension(const std::string& filePath, const std::string& ext)
{
	std::string extname;
	GetExtension(filePath, extname);

	if (extname == ext)
	{
		return true;
	}
	else
	{
		return false;
	}
}
}
}