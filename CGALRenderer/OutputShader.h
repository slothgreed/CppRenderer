#ifndef OUTPUT_SHADER_H
#define OUTPUT_SHADER_H

namespace KI
{

class OutputShader : public IShader
{
	enum UNIFORM_LOCATION : unsigned short
	{
		UNIFORM_LOCATION_COLOR_TEXTURE,
		UNIFORM_LOCATION_NUM
	};
public:
	OutputShader();
	~OutputShader();
	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_OUTPUT; }
	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;

private:
	void BindTexture(GLint activeNumber, GLint textureId);

	GLint m_uniformLocation[UNIFORM_LOCATION_NUM];

};

}


#endif OUTPUT_SHADER_H