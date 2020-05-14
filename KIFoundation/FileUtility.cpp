#include <filesystem>

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

bool FileUtility::Load(const string& filePath, string& contents)
{
	if (IsExist(filePath))
	{
		Logger::Output(LOG_LEVEL::ERROR, "file open error");
		return false;
	}

	std::ifstream ifs(filePath);
	std::string line;
	while ((getline(ifs, line)))
	{
		contents += line + "\n";
	}

	return true;
}


bool FileUtility::Load(const string& filePath, vector<string>& lines)
{
	if (IsExist(filePath))
	{
		Logger::Output(LOG_LEVEL::ERROR, "file open error");
		return false;
	}

	ifstream ifs(filePath);
	string line;
	while ((getline(ifs, line)))
	{
		lines.push_back(line);
	}

	return true;
}


bool FileUtility::IsExist(const string& filePath)
{
	ifstream fs(filePath);
	return fs.is_open();
}

void FileUtility::GetExtension(const string& filePath, string& ext)
{
	int index = (int)filePath.find_last_of(".");
	ext = filePath.substr(index, filePath.size() - index);
}

void FileUtility::GetDirectoryPath(const string& filePath, string& directoryPath)
{
	int index = (int)filePath.find_last_of("\"");
	directoryPath = filePath.substr(index, filePath.size() - index);
}
bool FileUtility::CheckExtension(const string& filePath, const string& ext)
{
	string extname;
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