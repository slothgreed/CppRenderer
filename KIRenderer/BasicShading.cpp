
namespace KI
{
namespace Renderer
{
BasicFragCode::BasicFragCode(BASIC_SHADING_TYPE type)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_BASICSHADING) +
		string(SHADER_EXT_FRAG))
{
	m_Type = type;
}

BasicFragCode::~BasicFragCode()
{
}

void BasicFragCode::GetDefineCode(string& code)
{
	if (m_Type == BASIC_SHADING_TYPE_FIXCOLOR)
		code += "#define VIEW_FIXCOLOR\n";
	if (m_Type == BASIC_SHADING_TYPE_TEXTURE)
		code += "#define VIEW_TEXTURE\n";
}

bool BasicFragCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<BasicFragCode*>(pShaderCode);
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

void BasicFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pShading = static_pointer_cast<BasicShading>(pShaderChunk);
	if (pShading == nullptr)
	{
		assert(0);
	}

	if (m_Type == BASIC_SHADING_TYPE_FIXCOLOR)
	{
		IShaderCode::BindVector4(m_uniformLocation[BASIC_SHADING_TYPE_FIXCOLOR], pShading->GetColor());
	}
	else
	{
		pShading->GetTexture()->Begin();
		IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[BASIC_SHADING_TYPE_TEXTURE]);
	}

}

void BasicFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pShading = static_pointer_cast<BasicShading>(pShaderChunk);
	if (pShading != nullptr)
	{
		if (m_Type == BASIC_SHADING_TYPE_TEXTURE)
		{
			pShading->GetTexture()->End();
		}
	}
}

void BasicFragCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(BASIC_SHADING_TYPE_NUM);
	m_uniformLocation[BASIC_SHADING_TYPE_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	m_uniformLocation[BASIC_SHADING_TYPE_FIXCOLOR] = glGetUniformLocation(programId, "uFixColor");
	Logger::GLError();
}

BasicShading::BasicShading(const vec4& color)
{
	SetColor(color);
}

BasicShading::BasicShading(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

BasicShading::~BasicShading()
{
}

void BasicShading::SetColor(const vec4& color)
{
	m_color = color;
	m_Type = BASIC_SHADING_TYPE_FIXCOLOR;
}

void BasicShading::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pTexture = pTexture;
	m_Type = BASIC_SHADING_TYPE_TEXTURE;
}

bool BasicShading::Compare(IShading* pShading)
{
	auto pBasicShading = dynamic_cast<BasicShading*>(pShading);
	if (pBasicShading != nullptr)
	{
		if (m_Type == pBasicShading->ColorType())
		{
			return true;
		}
	}

	return false;
}
shared_ptr<IShaderCode> BasicShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		VERTEX_LAYOUT layout = VERTEX_LAYOUT_NONE;
		if (m_Type == BASIC_SHADING_TYPE_FIXCOLOR)
		{
			layout = VERTEX_LAYOUT_NONE;
		}
		else if(m_Type == BASIC_SHADING_TYPE_TEXTURE)
		{
			layout = VERTEX_LAYOUT_TEXCOORD;
		}

		return make_shared<DefaultVertexCode>(layout);
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<BasicFragCode>(m_Type);
	}
	else
	{
		return nullptr;
	}
}

bool BasicShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetShading = dynamic_cast<BasicShading*>(pTarget);
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