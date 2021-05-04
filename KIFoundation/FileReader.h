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
	float ReadFloat();
	vec2 ReadVec2();
	vec3 ReadVec3();
	vec4 ReadVec4();
	bool EndOfFile();
	void Close();
private:
	std::ifstream m_fileStream;
};

}
}
#endif FILE_READER_H