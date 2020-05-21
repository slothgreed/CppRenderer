#include "glm/gtc/type_ptr.hpp"
namespace KI
{
namespace Gfx
{

void IShaderCode::Load(string& code)
{
	string defineCode;
	GetDefineCode(defineCode);
	string fileCode;
	ShaderUtility::Load(m_filePath, fileCode);
	code = defineCode + fileCode;
}

void IShaderCode::BindTexture(GLint activeNumber, GLint uniformId)
{
	glActiveTexture(activeNumber);
	Logger::GLError();

	glUniform1i(uniformId, activeNumber - GL_TEXTURE0);
	Logger::GLError();
}

void IShaderCode::BindInt(GLint uniformId, int value)
{
	glUniform1i(uniformId, value);
	Logger::GLError();
}
void IShaderCode::BindFloat(GLint uniformId, float value)
{
	glUniform1f(uniformId, value);
	Logger::GLError();
}
void IShaderCode::BindVector3(GLint uniformId, vec3 value)
{
	glUniform3fv(uniformId, 1, glm::value_ptr(value));
	Logger::GLError();
}

void IShaderCode::BindVector4(GLint uniformId, vec4 value)
{
	glUniform4fv(uniformId, 1, glm::value_ptr(value));
	Logger::GLError();
}

}
}