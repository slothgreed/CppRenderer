#ifndef DEFAULT_SHADER_H
#define DEFAULT_SHADER_H


class IShader;
class DefaultShader : public IShader
{
public:
	DefaultShader();
	~DefaultShader();
	static void GetVertexShaderDefine(VERTEX_LAYOUT layout, std::string& vertexFilePath);

	virtual void Initialize() override;

private:
	void BindScene();
};

#endif DEFAULT_SHADER_H