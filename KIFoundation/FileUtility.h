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

	static bool IsExist(const string& filePath);
	static bool Load(const string& filePath, string& contents);
	static bool Load(const string& filePath, vector<string>& contents);
	static void GetExtension(const string& filePath, string& ext);
	static void GetDirectoryPath(const string& filePath, string& directoryPath);
	static bool CheckExtension(const string& filePath, const string& ext);
private:

};
}
}
#endif FILE_UTILITY_H