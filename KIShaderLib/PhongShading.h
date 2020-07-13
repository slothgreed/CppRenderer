#ifndef PHONG_SHADING_H
#define PHONG_SHADING_H

namespace KI
{
namespace ShaderLib
{

enum PHONG_SHADING_TYPE : unsigned int
{
	PHONG_SHADING_TYPE_PHONG,
	PHONG_SHADING_TYPE_BLIN,
	PHONG_SHADING_TYPE_COOKTRANCE,
	PHONG_SHADING_TYPE_NUM
};

struct ADSShadingData
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

class PhongShadingFragCode : public IShaderCode
{
public:
	PhongShadingFragCode(PHONG_SHADING_TYPE type, SHADING_COLOR_TYPE colorType);
	~PhongShadingFragCode();
	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override;

private:
	PHONG_SHADING_TYPE m_Type;
	shared_ptr<GetColorCode> m_pColorCode;

};

class DLL_EXPORT PhongShading : public IShading
{
public:
	PhongShading(PHONG_SHADING_TYPE type, SHADING_COLOR_TYPE colorType, const ADSShadingData& data);
	~PhongShading();

	void Set(const ADSShadingData& adsData);
	bool NewShaderCompare(IShaderChunk* pTarget);
	shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo, SHADER_PROGRAM_TYPE type);

private:
	PHONG_SHADING_TYPE m_Type;
	SHADING_COLOR_TYPE m_ColorType;
	ADSShadingData m_ADSData;
	
};

}
}
#endif
