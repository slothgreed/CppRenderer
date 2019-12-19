#ifndef COMPOSIT_SHADERL_H
#define COMPOSIT_SHADERL_H

namespace KI
{

class CompositShader : public IShader
{
	enum COMPOSIT_TYPE
	{
		COMPOSIT_TYPE_ADD,
		COMPOSIT_TYPE_SUB,
		COMPOSIT_TYPE_MULT,
		COMPOSIT_TYPE_OVERWRITE,
		COMPOSIT_TYPE_NUM
	};
	enum COMPOSIT_UNIFORM : unsigned short
	{
		COMPOSIT_UNIFORM_SOURCE_TEXTURE,
		COMPOSIT_UNIFORM_TARGET_TEXTURE,
		COMPOSIT_UNIFORM_NUM
	};
public:
	CompositShader();
	~CompositShader();
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_COMPOSIT; }

	virtual void Initialize();
	virtual void FetchUniformLocation();
	virtual void SetSourceTexture(shared_ptr<Texture> source);
	virtual void SetTargetTexture(shared_ptr<Texture> target);
	virtual void BindTexture(GLint activeNumber, GLint textureId);
	static void GetFragShaderDefine(COMPOSIT_TYPE layout, ShaderBuildInfo& shaderDefine);


private:
	GLint m_uniformLocation[COMPOSIT_UNIFORM_NUM];
	shared_ptr<Texture> m_pSource;
	shared_ptr<Texture> m_pTarget;
};

#define FRAG_SHADER_COMPOSIT_ADD		"#define COMPOSIT_ADD\n"
#define FRAG_SHADER_COMPOSIT_SUB		"#define COMPOSIT_SUB\n"
#define FRAG_SHADER_COMPOSIT_MULT		"#define COMPOSIT_MULT\n"
#define FRAG_SHADER_COMPOSIT_OVERWRITE	"#define COMPOSIT_OVERWRITE\n"
}

#endif COMPOSIT_SHADERL_H
