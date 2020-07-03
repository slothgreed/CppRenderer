#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
namespace Renderer
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
};

class UniformStruct : public IUniform
{
public:
	UniformStruct() {};
	~UniformStruct() {};

	void SetLight(shared_ptr<UniformLight> value) { m_pLight = value; };
	void SetScene(shared_ptr<UniformScene> value) { m_pScene = value; };
	void SetModel(shared_ptr<UniformModel> value) { m_pModel = value; };
	void SetMaterial(shared_ptr<UniformMaterial> value) { m_pMaterial = value; };
private:
	shared_ptr<UniformLight> m_pLight;
	shared_ptr<UniformMaterial> m_pMaterial;
	shared_ptr<UniformScene> m_pScene;
	shared_ptr<UniformModel> m_pModel;
};

}
}
#endif DEFAULT_SHADER_H

