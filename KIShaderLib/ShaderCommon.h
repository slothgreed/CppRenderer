#ifndef SHADER_COMMON_CODE_H
#define SHADER_COMMON_CODE_H

namespace KI
{
namespace ShaderLib
{

class DLL_EXPORT ShaderCommon : public IShaderCode
{
public:
	ShaderCommon()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_COMMON) +
			string(SHADER_EXT_TXT)) {}
	~ShaderCommon() {};

	virtual void Initialize(GLuint programId) override {};
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};

private:

};

}
}

#endif SHADER_COMMON_CODE_H