
namespace KI
{
namespace Asset
{

BasicMaterialVertexCode::BasicMaterialVertexCode()
	:IShaderCode(
		string(SHADER_DIRECTORY)+
		string(SHADER_BASICMATERIAL)+
		string(SHADER_EXT_VERTEX)
	)
{
	Load(m_Code);
}

BasicMaterialFragCode::BasicMaterialFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_BASICMATERIAL) +
		string(SHADER_EXT_FRAG)
	)
{
	Load(m_Code);
}

BasicMaterial::BasicMaterial()
{
	SetColor(vec4(1, 1, 0, 1));
}

BasicMaterial::BasicMaterial(const vec4& color)
{
	SetColor(color);
}

BasicMaterial::BasicMaterial(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

BasicMaterial::BasicMaterial(BASIC_MATERIAL_TYPE type)
{
	if (type == BASIC_MATERIAL_TYPE_FIXCOLOR ||
		type == BASIC_MATERIAL_TYPE_TEXTURE)
	{
		assert(0);
		SetColor(vec4(1, 1, 0, 1));
	}
	else
	{
		m_Type = type;
	}
}

BasicMaterial::~BasicMaterial()
{
}

void BasicMaterial::SetColor(const vec4& color)
{
	m_color = color;
	m_Type = BASIC_MATERIAL_TYPE_FIXCOLOR;
}

void BasicMaterial::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pTexture = pTexture;
	m_Type = BASIC_MATERIAL_TYPE_TEXTURE;
}

void BasicMaterial::GetEmbeddedCode(SHADER_PROGRAM_TYPE& type, string& code)
{
	code.clear();
	code += "#define USE_MATERIAL\n";
	switch (m_Type)
	{
	case BASIC_MATERIAL_TYPE_VERTEXCOLOR:
		code += "#define VIEW_VERTEXCOLOR\n";
		break;
	case BASIC_MATERIAL_TYPE_NORMAL:
		code += "#define VIEW_NORMAL\n";
		break;
	case BASIC_MATERIAL_TYPE_TEXCOORD:
		code += "#define VIEW_TEXCOORD\n";
		break;
	case BASIC_MATERIAL_TYPE_DEPTH:
		code += "#define VIEW_DEPTH\n";
		break;
	case BASIC_MATERIAL_TYPE_FIXCOLOR:
		code += "#define VIEW_FIXCOLOR\n";
		break;
	case BASIC_MATERIAL_TYPE_TEXTURE:
		code += "#define VIEW_TEXTURE\n";
	break;
	default:
		assert(0);
		break;
	}

	if (m_Type == BASIC_MATERIAL_TYPE_VERTEXCOLOR ||
		m_Type == BASIC_MATERIAL_TYPE_NORMAL ||
		m_Type == BASIC_MATERIAL_TYPE_TEXCOORD ||
		m_Type == BASIC_MATERIAL_TYPE_DEPTH ||
		m_Type == BASIC_MATERIAL_TYPE_FIXCOLOR)
	{
		type = SHADER_PROGRAM_TYPE::SHADER_PROGRAM_VERTEX;
		string vertexCode;
		if (vertexCode.empty())
		{
			FileUtility::Load(
				string(SHADER_DIRECTORY) +
				string(SHADER_BASICMATERIAL) +
				string(SHADER_EXT_VERTEX), vertexCode);
		}
		code += vertexCode;
	}
	else if (m_Type == BASIC_MATERIAL_TYPE_TEXTURE)
	{
		type = SHADER_PROGRAM_TYPE::SHADER_PROGRAM_FRAG;
		string fragCode;
		if (fragCode.empty())
		{
			FileUtility::Load(
				string(SHADER_DIRECTORY) +
				string(SHADER_BASICMATERIAL) +
				string(SHADER_EXT_VERTEX), fragCode);
		}
		code += fragCode;
	}
	else
	{
		assert(0);
	}
}

void BasicMaterial::Initialize()
{
	
}
void BasicMaterial::FetchUniformLocation(GLuint programId)
{
	m_uniformLocation.resize(BASICMATERIAL_UNIFORM_NUM);
	m_uniformLocation[BASICMATERIAL_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	m_uniformLocation[BASICMATERIAL_UNIFORM_FIX_COLOR] = glGetUniformLocation(programId, "uFixColor");
	Logger::GLError();
}

void BasicMaterial::Bind()
{
	if (m_Type == BASIC_MATERIAL_TYPE_FIXCOLOR)
	{
		BindFixColor();
	}
	else if(m_Type == BASIC_MATERIAL_TYPE_TEXTURE)
	{
		m_pTexture->Begin();
		BindColorTexture();
	}
}

void BasicMaterial::UnBind()
{
	if (m_Type == BASIC_MATERIAL_TYPE_TEXTURE)
	{
		m_pTexture->End();
	}
}

void BasicMaterial::BindColorTexture()
{
	if (m_uniformLocation[BASICMATERIAL_UNIFORM_COLOR_TEXTURE] == -1)
	{
		assert(0);
		return;
	}

	IShader::BindTexture(GL_TEXTURE0, m_uniformLocation[BASICMATERIAL_UNIFORM_COLOR_TEXTURE]);
}

void BasicMaterial::BindFixColor()
{
	if (m_uniformLocation[BASICMATERIAL_UNIFORM_FIX_COLOR] == -1)
	{
		assert(0);
		return;
	}

	IShader::BindVector4(m_uniformLocation[BASICMATERIAL_UNIFORM_FIX_COLOR], m_color);
}

}
}
