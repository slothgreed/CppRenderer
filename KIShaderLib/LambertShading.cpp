namespace KI
{
namespace ShaderLib
{


LambertFragCode::LambertFragCode(LAMBERT_SHADING_TYPE type)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_LAMBERTSHADING) +
		string(SHADER_EXT_FRAG))
{
	m_Type = type;
}

LambertFragCode::~LambertFragCode()
{
}

void LambertFragCode::GetDefineCode(string& code)
{
	if (m_Type == LAMBERT_SHADING_TYPE_FIXCOLOR)
		code += "#define IN_FIXCOLOR\n";
	if (m_Type == LAMBERT_SHADING_TYPE_TEXTURE)
		code += "#define IN_TEXTURE\n";
	if (m_Type == LAMBERT_SHADING_TYPE_VERTEXCOLOR)
		code += "#define IN_COLOR\n";
}

bool LambertFragCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<LambertFragCode*>(pShaderCode);
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

void LambertFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = static_pointer_cast<LambertShading>(pShaderChunk);
	if (pShading == nullptr)
	{
		assert(0);
	}

	if (m_Type == LAMBERT_SHADING_TYPE_FIXCOLOR)
	{
		IShaderCode::BindVector4(m_uniformLocation[LAMBERT_SHADING_TYPE_FIXCOLOR], pShading->GetColor());
	}
	else
	{
		pShading->GetTexture()->Begin();
		IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[LAMBERT_SHADING_TYPE_TEXTURE]);
	}

}

void LambertFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = static_pointer_cast<LambertShading>(pShaderChunk);
	if (pShading != nullptr)
	{
		if (m_Type == LAMBERT_SHADING_TYPE_TEXTURE)
		{
			pShading->GetTexture()->End();
		}
	}
}

void LambertFragCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(LAMBERT_SHADING_TYPE_NUM);
	m_uniformLocation[LAMBERT_SHADING_TYPE_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	m_uniformLocation[LAMBERT_SHADING_TYPE_FIXCOLOR] = glGetUniformLocation(programId, "uFixColor");
	Logger::GLError();
}

LambertShading::LambertShading(const vec4& color)
{
	SetColor(color);
}

LambertShading::LambertShading(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

void LambertShading::SetColor(const vec4& color)
{
	m_color = color;
	m_Type = LAMBERT_SHADING_TYPE_FIXCOLOR;
}

void LambertShading::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pTexture = pTexture;
	m_Type = LAMBERT_SHADING_TYPE_TEXTURE;
}

bool LambertShading::Compare(IShading* pShading)
{
	auto pLambertShading = dynamic_cast<LambertShading*>(pShading);
	if (pLambertShading != nullptr)
	{
		if (m_Type == pLambertShading->ColorType())
		{
			return true;
		}
	}

	return false;
}
shared_ptr<IShaderCode> LambertShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		VERTEX_LAYOUT outLayout = VERTEX_LAYOUT_NONE;
		if (m_Type == LAMBERT_SHADING_TYPE_VERTEXCOLOR)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_COLOR);
		}
		else if (m_Type == LAMBERT_SHADING_TYPE_TEXTURE)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_TEXCOORD);
		}
		else if(m_Type == LAMBERT_SHADING_TYPE_FIXCOLOR)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL);
		}
		else
		{
			assert(0);
		}

		return make_shared<DefaultVertexCode>(outLayout);

	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<LambertFragCode>(m_Type);
	}
	else
	{
		return nullptr;
	}
}

bool LambertShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetShading = dynamic_cast<LambertShading*>(pTarget);
	if (pTargetShading == nullptr)
	{
		return false;
	}

	if (ColorType() == pTargetShading->ColorType())
	{
		return true;
	}

	return false;
}
}
}