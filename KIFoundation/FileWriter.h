#ifndef FILE_WRITER_H
#define FILE_WRITER_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT FileWriter
{
public:
	FileWriter();
	~FileWriter();

	bool Open(const std::string& filePath);
	void Write(const std::string& contents, bool endl = false);
	void Close();
private:
	std::ofstream m_fileStream;
};

}
}
#endif FILE_UTILITY_H