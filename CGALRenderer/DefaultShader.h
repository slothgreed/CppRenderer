#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H

namespace KI
{
class IShader;
class DefaultShader : public IShader
{
	enum UNIFORM_LOCATION : unsigned short
	{
		UNIFORM_LOCATION_COLOR_TEXTURE,
		UNIFORM_LOCATION_NUM
	};
public:
	DefaultShader();
	~DefaultShader();
	static void GetVertexShaderDefine(VERTEX_LAYOUT layout, ShaderBuildInfo& buildInfo);
	static void GetFragShaderDefine(VERTEX_LAYOUT layout, ShaderBuildInfo& shaderDefine);

	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;

	GLint m_uniformLocation[UNIFORM_LOCATION_NUM];
private:
	void BindScene();
	void BindTexture(GLint activeNumber, GLint textureId);

};


#define VERTEX_SHADER_USE_NORMAL	"#define USE_NORMAL\n"
#define VERTEX_SHADER_USE_COLOR		"#define USE_COLOR\n"
#define VERTEX_SHADER_USE_TEXCOORD	"#define USE_TEXCOORD\n"
#define FRAG_SHADER_USE_TECOORD		"#define USE_TEXCOORD\n"
#define FRAG_SHADER_USE_TEXTURE0	"#define USE_TEXTURE0\n"
}
#endif DEFAULT_SHADER_H