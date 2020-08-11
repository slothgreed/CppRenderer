#ifndef CUBE_SPACE_H
#define CUBE_SPACE_H
namespace KI
{
namespace Asset
{

class DLL_EXPORT CubeSpaceArgs
{
public:
	CubeSpaceArgs(BDB _size) : size(_size) {}
	BDB size;
};
class  DLL_EXPORT CubeSpace : public IPrimitive
{

public:
	CubeSpace(const CubeSpaceArgs& args);
	~CubeSpace();
	void Build(const CubeSpaceArgs& args);

private:

};


}
}
#endif CUBE_SPACE_H
