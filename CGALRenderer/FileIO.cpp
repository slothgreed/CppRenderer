FileIO::FileIO()
{
}

FileIO::~FileIO()
{
}

bool FileIO::Load(const std::string& filePath, std::string& contents)
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