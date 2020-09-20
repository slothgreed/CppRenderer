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
	string tcsCode;
	string tesCode;
	string geomCode;
	string fragCode;
	GetShaderCode(SHADER_PROGRAM_VERTEX, vertexCode);
	GetShaderCode(SHADER_PROGRAM_TCS,	tcsCode);
	GetShaderCode(SHADER_PROGRAM_TESS,	tesCode);
	GetShaderCode(SHADER_PROGRAM_GEOM,	geomCode);
	GetShaderCode(SHADER_PROGRAM_FRAG,	fragCode);
	
	debug_vertexCode = vertexCode;
	debug_tcsCode	= tcsCode;
	debug_tesCode	= tesCode;
	debug_geomCode	= geomCode;
	debug_fragCode	= fragCode;

	BuildFromCode(vertexCode, tcsCode, tesCode, geomCode, fragCode);

	Initialize();
}

void IShader::GetShaderCode(SHADER_PROGRAM_TYPE type, string& code)
{
	auto pCode = BuildInfo()->GetShaderChunk()->NewShaderCode(BuildInfo().get(), type);
	if (pCode == nullptr)
	{
		return;
	}

	string shaderCode;
	pCode->Load(shaderCode);
	pCode->GetIncludeCode(m_pIncludeCode);
	auto pVBOCode = pCode->GetVertexBufferCode(BuildInfo()->GetVertexBuffer());
	string includeDefine;
	for (int i = 0; i < m_pIncludeCode.size(); i++)
	{
		string defineCode;
		m_pIncludeCode[i]->GetDefineCode(defineCode);
		includeDefine += defineCode;
	}

	string vboDefine;
	if (pVBOCode != nullptr)
	{
		pVBOCode->GetDefineCode(vboDefine);
	}

	code = string("#version 400 core\n") + includeDefine + vboDefine + shaderCode;

	m_pShaderCodes[type] = pCode;
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
	if (fragCode != "")
		fragId = ShaderUtility::Compile(fragCode, GL_FRAGMENT_SHADER);

	m_programId = ShaderUtility::Link(vertId, tcsId, tesId, geomId, fragId);
}

void IShader::Initialize()
{
	for (int i = 0; i < m_pIncludeCode.size(); i++)
	{
		m_pIncludeCode[i]->Initialize(m_programId);
	}


	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		if (m_pShaderCodes[i] == nullptr)
		{
			continue;
		}

		m_pShaderCodes[i]->Initialize(m_programId);
	}
}

void IShader::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	for (int i = 0; i < m_pIncludeCode.size(); i++)
	{
		m_pIncludeCode[i]->Bind(pShaderChunk, pUniform);
	}

	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		if (m_pShaderCodes[i] == nullptr)
		{
			continue;
		}

		m_pShaderCodes[i]->Bind(pShaderChunk, pUniform);
	}
}

void IShader::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	for (int i = 0; i < m_pIncludeCode.size(); i++)
	{
		m_pIncludeCode[i]->UnBind(pShaderChunk, pUniform);
	}

	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		if (m_pShaderCodes[i] == nullptr)
		{
			continue;
		}

		m_pShaderCodes[i]->UnBind(pShaderChunk, pUniform);
	}
}

void IShader::Use()
{
	if (m_programId == 0)
	{
		Logger::Output(LOG_LEVEL::LOG_LEVEL_ERROR, "Not call Initialize");
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