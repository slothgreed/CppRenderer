namespace KI
{
namespace ShaderLib
{

GetColorCode::GetColorCode(SHADING_COLOR_TYPE type)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_LAMBERTSHADING) +
		string(SHADER_EXT_FRAG))
{
	m_Type = type;
}

GetColorCode::~GetColorCode()
{
}

void GetColorCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_NUM);
	m_uniformLocation[SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	m_uniformLocation[SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_FIXCOLOR] = glGetUniformLocation(programId, "uFixColor");
	Logger::GLError();
}

void GetColorCode::GetDefineCode(string& code)
{
	if (m_Type == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_FIXCOLOR)
		code += "#define IN_FIXCOLOR\n";
	if (m_Type == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_TEXTURE)
		code += "#define IN_TEXTURE\n";
	if (m_Type == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_VERTEXCOLOR)
		code += "#define IN_COLOR\n";
}

bool GetColorCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<GetColorCode*>(pShaderCode);
	if (pCode == nullptr)
	{
		return false;
	}

	if (m_Type == pCode->Type())
	{
		return true;
	}


	return false;
}

void GetColorCode::Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<LambertShading*>(pShaderChunk.get());
	if (pShading == nullptr)
	{
		assert(0);
	}

	if (m_Type == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_FIXCOLOR)
	{
		IShaderCode::BindVector4(m_uniformLocation[SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_FIXCOLOR], pShading->GetColor());
	}
	else if(m_Type == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_TEXTURE)
	{
		pShading->GetTexture()->Begin();
		IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_FIXCOLOR]);
	}

}

void GetColorCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<LambertShading*>(pShaderChunk.get());
	if (pShading != nullptr)
	{
		if (m_Type == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_TEXTURE)
		{
			pShading->GetTexture()->End();
		}
	}
}

}
}