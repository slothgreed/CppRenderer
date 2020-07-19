#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT ShaderStruct : public IShaderCode
{
public:
	ShaderStruct();
	~ShaderStruct();
	virtual void Initialize(GLuint programId) override;
	virtual bool Compare(IShaderCode* pShaderCode) override { return true; };
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)  override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)  override;

private:
	void BindScene(GLuint programId);
	void BindLight(GLuint programId);
	void BindMaterial(GLuint programId);
	void BindModel(GLuint programId);
};


}
}
#endif DEFAULT_SHADER_H

