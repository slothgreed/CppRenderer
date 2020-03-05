#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT FileUtility
{
public:
	FileUtility();
	~FileUtility();

	static bool Load(const std::string& filePath, std::string& contents);
	static void GetExtension(const std::string& filePath, std::string& ext);
	static bool CheckExtension(const std::string& filePath, const std::string& ext);
private:

};
}
}
#endif FILE_UTILITY_H