
namespace KI
{
namespace Renderer
{
BasicMaterialFragCode::BasicMaterialFragCode(BASIC_MATERIAL_TYPE type)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_BASICMATERIAL) +
		string(SHADER_EXT_FRAG))
{
	m_Type = type;
}

BasicMaterialFragCode::~BasicMaterialFragCode()
{
}

void BasicMaterialFragCode::GetDefineCode(string& code)
{
	if (m_Type == BASIC_MATERIAL_TYPE_FIXCOLOR)
		code += "#define VIEW_FIXCOLOR\n";
	if (m_Type == BASIC_MATERIAL_TYPE_TEXTURE)
		code += "#define VIEW_TEXTURE\n";
}

bool BasicMaterialFragCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<BasicMaterialFragCode*>(pShaderCode);
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

void BasicMaterialFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = static_pointer_cast<BasicMaterial>(pShaderChunk);
	if (pMaterial == nullptr)
	{
		assert(0);
	}

	if (m_Type == BASIC_MATERIAL_TYPE_FIXCOLOR)
	{
		IShaderCode::BindVector4(m_uniformLocation[BASIC_MATERIAL_TYPE_FIXCOLOR], pMaterial->GetColor());
	}
	else
	{
		pMaterial->GetTexture()->Begin();
		IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[BASIC_MATERIAL_TYPE_TEXTURE]);
	}

}

void BasicMaterialFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = static_pointer_cast<BasicMaterial>(pShaderChunk);
	if (pMaterial != nullptr)
	{
		if (m_Type == BASIC_MATERIAL_TYPE_TEXTURE)
		{
			pMaterial->GetTexture()->End();
		}
	}
}

void BasicMaterialFragCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(BASIC_MATERIAL_TYPE_NUM);
	m_uniformLocation[BASIC_MATERIAL_TYPE_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	m_uniformLocation[BASIC_MATERIAL_TYPE_FIXCOLOR] = glGetUniformLocation(programId, "uFixColor");
	Logger::GLError();
}

BasicMaterial::BasicMaterial(const vec4& color)
{
	SetColor(color);
}

BasicMaterial::BasicMaterial(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
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

bool BasicMaterial::Compare(IMaterial* pMaterial)
{
	auto pBasicMaterial = dynamic_cast<BasicMaterial*>(pMaterial);
	if (pBasicMaterial != nullptr)
	{
		if (m_Type == pBasicMaterial->ColorType())
		{
			return true;
		}
	}

	return false;
}
shared_ptr<IShaderCode> BasicMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		VERTEX_LAYOUT layout = VERTEX_LAYOUT_NONE;
		if (m_Type == BASIC_MATERIAL_TYPE_FIXCOLOR)
		{
			layout = VERTEX_LAYOUT_NONE;
		}
		else if(m_Type == BASIC_MATERIAL_TYPE_TEXTURE)
		{
			layout = VERTEX_LAYOUT_TEXCOORD;
		}

		return make_shared<DefaultVertexCode>(layout);
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<BasicMaterialFragCode>(m_Type);
	}
	else
	{
		return nullptr;
	}
}

bool BasicMaterial::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetMaterial = dynamic_cast<BasicMaterial*>(pTarget);
	if (pTargetMaterial == nullptr)
	{
		return false;
	}

	if (ColorType() == pTargetMaterial->ColorType())
	{
		return true;
	}

	return false;
}
}
}