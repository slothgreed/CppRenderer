#ifndef ISHADERCHUNKL_H
#define ISHADERCHUNKL_H
namespace KI
{
namespace Gfx
{
class IShaderBuildInfo;
class DLL_EXPORT IShaderChunk
{
public:
	IShaderChunk() {};
	virtual ~IShaderChunk() {};
	virtual bool NewShaderCompare(IShaderChunk* pTarget) = 0;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) = 0;
private:

};
}
}

#endif ISHADERCHUNKL_H
