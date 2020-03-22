#include "glm/gtc/type_ptr.hpp"
namespace KI
{
namespace Gfx
{
void IShader::Build(shared_ptr<IShaderDefine> pShaderDefine)
{
	m_pShaderDefine = pShaderDefine;
	GenerateShaderCode(pShaderDefine.get());
}

void IShader::GenerateShaderCode(IShaderDefine* pShaderDefine)
{
	string vertexCode;
	string fragCode;
	string geomCode;
	GetShaderCode(SHADER_PROGRAM_VERTEX, vertexCode);
	GetShaderCode(SHADER_PROGRAM_GEOM, geomCode);
	GetShaderCode(SHADER_PROGRAM_FRAG, fragCode);
	
#ifdef SHADER_DEBUG
	debug_vertexShader = vertexCode;
	debug_geomShader = geomCode;
	debug_fragShader = fragCode;
#endif

	BuildFromCode(vertexCode, fragCode);
}

void IShader::GetShaderCode(
	SHADER_PROGRAM_TYPE type,
	string& code)
{
	if (m_shaderPath[type] == "")
	{
		return;
	}

	string shaderCode;
	FileUtility::Load(m_shaderPath[type], shaderCode);
	string shaderDefine;
	m_pShaderDefine->GetDefineCode(type, shaderDefine);

	code = m_version + shaderDefine + shaderCode;
}

void IShader::BuildFromCode(const string& vertexShaderCode, const string& fragmentShader)
{
	GLuint vertId = ShaderUtility::Compile(vertexShaderCode, GL_VERTEX_SHADER);
	GLuint fragId = ShaderUtility::Compile(fragmentShader, GL_FRAGMENT_SHADER);

	m_programId = ShaderUtility::Link(vertId, fragId);
	Initialize();
	//UniformValidation();
}

bool IShader::UniformValidation()
{
	// defineÇ…ÇÊÇ¡ÇƒíËã`Ç≥ÇÍÇ»Ç¢uniformÇ‡Ç†ÇÈÅB
	for (int i = 0; i < m_uniformLocation.size(); i++)
	{
		if (m_uniformLocation[i] == -1)
		{
			Logger::Output(LOG_LEVEL::ERROR, "Need Call FetchUniformLocation on Initialize. And Set UniformParameter");
			return false;
		}
	}

	return true;
}

void IShader::Use()
{
	if (m_programId == 0)
	{
		Logger::Output(LOG_LEVEL::ERROR, "Not call Initialize");
	}

	glUseProgram(m_programId);
	Logger::GLError();

}

void IShader::UnUse()
{
	glUseProgram(0);
}

void IShader::Dispose()
{
	if (m_programId == 0)
	{
		glDeleteProgram(m_programId);
	}

	Logger::GLError();
}

void IShader::BindTexture(GLint activeNumber, GLint uniformId)
{
	if (m_programId == 0)
	{
		assert(0);
	}


	glActiveTexture(activeNumber);
	Logger::GLError();

	glUniform1i(uniformId, activeNumber - GL_TEXTURE0);
	Logger::GLError();
}

void IShader::BindVector4(GLint uniformId, vec4 value)
{
	glUniform4fv(uniformId, 1, glm::value_ptr(value));
	Logger::GLError();
}

bool IShader::Compare(IShaderDefine* shaderDefine)
{
	if (m_pShaderDefine->Compare(shaderDefine)) {
		return true;
	}
	else {
		return false;
	}
}
}
}