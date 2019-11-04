#ifndef FILE_IO_H
#define FILE_IO_H
class FileIO
{
public:
	FileIO();
	~FileIO();

	static bool Load(const std::string& filePath, std::string& contents);
private:

};

#endif FILE_IO_H