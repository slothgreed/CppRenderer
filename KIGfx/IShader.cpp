#include "glm/gtc/type_ptr.hpp"
namespace KI
{
namespace Gfx
{
void IShader::Build(shared_ptr<IShaderBuildInfo> pBuildInfo)
{
	m_pShaderBuildInfo = pBuildInfo;
	GenerateShaderCode(m_pShaderBuildInfo.get());
}

void IShader::GenerateShaderCode(IShaderBuildInfo* pBuildInfo)
{
	string vertexCode;
	string fragCode;
	string geomCode;
	GetShaderCode(SHADER_PROGRAM_VERTEX, vertexCode);
	GetShaderCode(SHADER_PROGRAM_GEOM, geomCode);
	GetShaderCode(SHADER_PROGRAM_FRAG, fragCode);
	
	BuildFromCode(vertexCode, fragCode);
}

void IShader::GetShaderCode(SHADER_PROGRAM_TYPE type, string& code)
{
	if (BuildInfo()->GetShaderCode(type) == nullptr)
	{
		return;
	}

	IShaderCode* pCode = BuildInfo()->GetShaderCode(type);

	string shaderCode;
	pCode->Load(shaderCode);
	string shaderDefine;
	pCode->GetDefineCode(shaderDefine);

	code = string("#version 400 core\n") +shaderDefine + shaderCode;
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

bool IShader::Compare(IShaderBuildInfo* shaderDefine)
{
	if (m_pShaderBuildInfo->Compare(shaderDefine)) {
		return true;
	}
	else {
		return false;
	}
}
}
}