#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H


class IShader;
class DefaultShader : public IShader
{
public:
	DefaultShader();
	~DefaultShader();
	static void GetVertexShaderDefine(VERTEX_LAYOUT layout, ShaderBuildInfo& buildInfo);

	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_DEFAULT; }

	virtual void Initialize() override;

private:
	void BindScene();


};


#define VERTEX_SHADER_USE_NORMAL	"#define USE_NORMAL\n"
#define VERTEX_SHADER_USE_COLOR		"#define USE_COLOR\n"
#define VERTEX_SHADER_USE_TEXCOORD	"#define USE_TEXCOORD\n"

#endif DEFAULT_SHADER_H