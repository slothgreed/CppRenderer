#ifndef IEMBEDDED_SHADERCODEL_H
#define IEMBEDDED_SHADERCODEL_H

namespace KI
{
namespace Gfx
{
#define EMBEDDEDCODE_AREA "<< EmbeddedCode Area >>"

class DLL_EXPORT IEmbeddedShaderCode
{
public:
	IEmbeddedShaderCode() {};
	virtual ~IEmbeddedShaderCode() {};
	virtual string GetName() = 0;

	virtual void Initialize() = 0;
	virtual void FetchUniformLocation(GLuint programId) = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	virtual void GetEmbeddedCode(SHADER_PROGRAM_TYPE& type, string& code) = 0;
private:
};
}
}
#endif IEMBEDDED_SHADERCODEL_H
