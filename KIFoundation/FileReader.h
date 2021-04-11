#ifndef FILE_READER_H
#define FILE_READER_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT FileReader
{
public:
	FileReader();
	~FileReader();

	bool Open(const std::string& filePath, bool binary = false);
	bool ReadLine(std::string& contents, bool endl = false);
	void* ReadBinary(Format format);
	bool EndOfFile();
	void Close();
private:
	std::ifstream m_fileStream;
};

}
}
#endif FILE_READER_H