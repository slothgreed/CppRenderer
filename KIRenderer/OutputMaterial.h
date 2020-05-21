#ifndef OUTPUT_MATERIAL_H
#define OUTPUT_MATERIAL_H

namespace KI
{
namespace Renderer
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
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk) override;
};
class DLL_EXPORT OutputMaterial : public IMaterial
{

public:
	OutputMaterial();
	~OutputMaterial();

	virtual shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type) override;
	bool Compare(IMaterial* pMaterial);
	void SetTexture(shared_ptr<Texture> pTexture) { m_pTexture = pTexture; };
	shared_ptr<Texture> GetTexture() { return m_pTexture; };
private:
	shared_ptr<Texture> m_pTexture;
};
}
}

#endif OUTPUT_MATERIAL_H