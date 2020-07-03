#ifndef POSTPROCESS_VERTEX_CODE_H
#define POSTPROCESS_VERTEX_CODE_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT PostProcessVertexCode : public IShaderCode
{
public:
	PostProcessVertexCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_POSTPROCESS) +
			string(SHADER_EXT_VERTEX)) {};
	~PostProcessVertexCode() {};

	virtual void Initialize(GLuint programId) override {};
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override {};
private:

};




}
}

#endif POSTPROCESS_VERTEX_CODE_H