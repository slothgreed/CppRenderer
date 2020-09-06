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
	IShaderChunk() :m_bNeedRecompileShader(true) {};
	virtual ~IShaderChunk() {};
	virtual bool NewShaderCompare(IShaderChunk* pTarget) = 0;
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) = 0;
	void CompiledShader() { m_bNeedRecompileShader = false; }
	bool NeedReCompileShader() { return m_bNeedRecompileShader; };
	virtual bool IsShading() { return false; };	// Vertex and Frag shader
	virtual bool HasShading() { return false; };  // geometry, tessellation
private:
	bool m_bNeedRecompileShader;

};
}
}

#endif ISHADERCHUNKL_H
