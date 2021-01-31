#ifndef ARRAY_CSV_IO_H
#define ARRAY_CSV_IO_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT ArrayCSVIO
{
public:
	ArrayCSVIO();
	~ArrayCSVIO();
	static void Output(const std::string& filePath, const vector<vec3>& value);

private:

};

}
}
#endif ARRAY_CSV_IO_H