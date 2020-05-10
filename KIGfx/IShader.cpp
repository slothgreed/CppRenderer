#include "glm/gtc/type_ptr.hpp"
namespace KI
{
namespace Gfx
{
void IShader::Build(shared_ptr<IShaderBuildInfo> pBuildInfo)
{
	m_pShaderBuildInfo = pBuildInfo;
	GenerateShaderCode(m_pShaderBuildInfo.get());
	Initialize();
	for (int i = 0; i < pBuildInfo->GetEmbeddedCodeSize(); i++)
	{
		pBuildInfo->GetEmbeddedCode(i)->FetchUniformLocation(m_programId);
	}
}

void IShader::GenerateShaderCode(IShaderBuildInfo* pBuildInfo)
{
	string shaderCode[SHADER_PROGRAM_NUM];

	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		GetShaderCode((SHADER_PROGRAM_TYPE)i, shaderCode[i]);
	}

	string embeddedCode[SHADER_PROGRAM_NUM];
	for (int i = 0; i < pBuildInfo->GetEmbeddedCodeSize(); i++)
	{
		auto pEmbedded = pBuildInfo->GetEmbeddedCode(i);
		SHADER_PROGRAM_TYPE type;
		string code;
		pEmbedded->GetEmbeddedCode(type, code);
		embeddedCode[type] += code;
	}

	string embeddedAreaStr = EMBEDDEDCODE_AREA;
	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		if (shaderCode[i].empty())
		{
			continue;
		}
		int pos = shaderCode[i].find(embeddedAreaStr);
		if (pos == -1)
		{
			continue;
		}
		
		string code = shaderCode[i].substr(0, pos);
		code += embeddedCode[i] + "\n";
		code += shaderCode[i].substr(pos + embeddedAreaStr.size(), shaderCode[i].size());
		shaderCode[i] = code;
	}

	BuildFromCode(
		shaderCode[SHADER_PROGRAM_VERTEX],
		shaderCode[SHADER_PROGRAM_TCS],
		shaderCode[SHADER_PROGRAM_TESS],
		shaderCode[SHADER_PROGRAM_GEOM],
		shaderCode[SHADER_PROGRAM_FRAG]);

	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		m_debugCode[i] = shaderCode[i];
	}
}

void IShader::GetShaderCode(SHADER_PROGRAM_TYPE type, string& code)
{
	if (BuildInfo()->GetShaderCode(type) == nullptr)
	{
		return;
	}

	auto pCode = BuildInfo()->GetShaderCode(type);

	string shaderCode;
	pCode->Load(shaderCode);
	string shaderDefine;
	pCode->GetDefineCode(shaderDefine);

	code = string("#version 400 core\n") +shaderDefine + shaderCode;
}

void IShader::BuildFromCode(const string& vertexCode, const string& tcsCode, const string& tesCode, const string& geomCode, const string& fragCode)
{
	GLuint vertId = 0;
	GLuint tcsId = 0;
	GLuint tesId = 0;
	GLuint geomId = 0;
	GLuint fragId = 0;
	
	if (vertexCode != "")
		vertId = ShaderUtility::Compile(vertexCode, GL_VERTEX_SHADER);
	if (tcsCode != "")
		tcsId = ShaderUtility::Compile(tcsCode, GL_TESS_CONTROL_SHADER);
	if (tesCode != "")
		tesId = ShaderUtility::Compile(tesCode, GL_TESS_EVALUATION_SHADER);
	if (geomCode != "")
		geomId = ShaderUtility::Compile(geomCode, GL_GEOMETRY_SHADER);
	if(fragCode != "")
		fragId = ShaderUtility::Compile(fragCode, GL_FRAGMENT_SHADER);

	m_programId = ShaderUtility::Link(vertId, tcsId, tesId, geomId, fragId);
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
	glActiveTexture(activeNumber);
	Logger::GLError();

	glUniform1i(uniformId, activeNumber - GL_TEXTURE0);
	Logger::GLError();
}

void IShader::BindInt(GLint uniformId, int value)
{
	glUniform1i(uniformId, value);
	Logger::GLError();
}
void IShader::BindFloat(GLint uniformId, float value)
{
	glUniform1f(uniformId, value);
	Logger::GLError();
}
void IShader::BindVector3(GLint uniformId, vec3 value)
{
	glUniform3fv(uniformId, 1, glm::value_ptr(value));
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