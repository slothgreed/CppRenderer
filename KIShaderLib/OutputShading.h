#ifndef OUTPUT_SHADING_H
#define OUTPUT_SHADING_H

namespace KI
{
namespace ShaderLib
{

class DLL_EXPORT OutputFragCode : public IShaderCode
{
public:
	enum UNIFORM_LOCATION : unsigned short
	{
		UNIFORM_LOCATION_COLOR_TEXTURE,
		UNIFORM_LOCATION_NUM
	};

	OutputFragCode()
		:IShaderCode(
			string(SHADER_DIRECTORY) +
			string(SHADER_OUTPUT) +
			string(SHADER_EXT_FRAG)) {};
	~OutputFragCode() {};
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_OUTPUT; }
	virtual void Initialize(GLuint programId);
	virtual bool Compare(IShaderCode* pShaderCode);
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform) override;
};
class DLL_EXPORT OutputShading : public IShading
{

public:
	OutputShading() {};
	OutputShading(shared_ptr<Texture> pTexture);
	~OutputShading();

	virtual bool NewShaderCompare(IShaderChunk* pTarget);
	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;
	bool Compare(IShading* pShading);
	void SetTexture(shared_ptr<Texture> pTexture) { m_pTexture = pTexture; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; };
private:
	shared_ptr<Texture> m_pTexture;
};
}
}

#endif OUTPUT_SHADING_H