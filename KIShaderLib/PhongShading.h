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

class PhongShadingFragCode : public IShaderCode
{
public:
	PhongShadingFragCode(PHONG_SHADING_TYPE type, SHADING_COLOR_TYPE colorType, const MaterialData& material);
	~PhongShadingFragCode();
	virtual void Initialize(GLuint programId) override;
	virtual void GetDefineCode(string& code) override;
	virtual bool Compare(IShaderCode* pShaderCode) override;
	virtual void Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override;
	virtual void UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform) override;

private:
	PHONG_SHADING_TYPE m_Type;
	shared_ptr<GetColorCode> m_pColorCode;
	MaterialData m_Material;

};

class DLL_EXPORT ADSMaterial
{
public:
	ADSMaterial() :
		m_ambient(vec4(1)),
		m_diffuse(vec4(1)),
		m_specular(vec4(1)),
		m_shinning(1.0) {}

	ADSMaterial(const vec4& ambient,
		const vec4& diffuse,
		const vec4& specular,
		float shinning) :
		m_ambient(ambient),
		m_diffuse(diffuse),
		m_specular(specular),
		m_shinning(shinning) {}

	~ADSMaterial() {};

	void SetAmbient(const vec4& ambient) { m_ambient = ambient; };
	void SetDiffuse(const vec4& diffuse) { m_diffuse = diffuse; };
	void SetSpecular(const vec4& specular) { m_specular = specular; };
	void SetShinning(float shinning) { m_shinning = shinning; };

	const vec4& GetAmbient() { return m_ambient; }
	const vec4& GetDiffuse() { return m_diffuse; }
	const vec4& GetSpecular() { return m_specular; }
	float GetShinning() { return m_shinning; }

private:
	vec4 m_ambient;
	vec4 m_diffuse;
	vec4 m_specular;
	float m_shinning;

};

class DLL_EXPORT PhongShading : public IShading, public IHasGetColor
{
public:
	PhongShading(PHONG_SHADING_TYPE type, SHADING_COLOR_TYPE colorType, const ADSMaterial& data);
	~PhongShading();

	void Set(const ADSMaterial& adsData);
	bool NewShaderCompare(IShaderChunk* pTarget);
	shared_ptr<IShaderCode> NewShaderCode(IShaderBuildInfo* pBuildInfo, SHADER_PROGRAM_TYPE type);

private:
	PHONG_SHADING_TYPE m_Type;
	SHADING_COLOR_TYPE m_ColorType;
	ADSMaterial m_ADSMaterial;
	
};

}
}
#endif
