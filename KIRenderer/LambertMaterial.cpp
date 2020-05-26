namespace KI
{
namespace Renderer
{


LambertMaterialFragCode::LambertMaterialFragCode(LAMBERT_MATERIAL_TYPE type)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_LAMBERTMATERIAL) +
		string(SHADER_EXT_FRAG))
{
	m_Type = type;
}

LambertMaterialFragCode::~LambertMaterialFragCode()
{
}

void LambertMaterialFragCode::GetDefineCode(string& code)
{
	if (m_Type == LAMBERT_MATERIAL_TYPE_FIXCOLOR)
		code += "#define IN_FIXCOLOR\n";
	if (m_Type == LAMBERT_MATERIAL_TYPE_TEXTURE)
		code += "#define IN_TEXTURE\n";
	if (m_Type == LAMBERT_MATERIAL_TYPE_VERTEXCOLOR)
		code += "#define IN_COLOR\n";
}

bool LambertMaterialFragCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<LambertMaterialFragCode*>(pShaderCode);
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

void LambertMaterialFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = static_pointer_cast<LambertMaterial>(pShaderChunk);
	if (pMaterial == nullptr)
	{
		assert(0);
	}

	if (m_Type == LAMBERT_MATERIAL_TYPE_FIXCOLOR)
	{
		IShaderCode::BindVector4(m_uniformLocation[LAMBERT_MATERIAL_TYPE_FIXCOLOR], pMaterial->GetColor());
	}
	else
	{
		pMaterial->GetTexture()->Begin();
		IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[LAMBERT_MATERIAL_TYPE_TEXTURE]);
	}

}

void LambertMaterialFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = static_pointer_cast<LambertMaterial>(pShaderChunk);
	if (pMaterial != nullptr)
	{
		if (m_Type == LAMBERT_MATERIAL_TYPE_TEXTURE)
		{
			pMaterial->GetTexture()->End();
		}
	}
}

void LambertMaterialFragCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(LAMBERT_MATERIAL_TYPE_NUM);
	m_uniformLocation[LAMBERT_MATERIAL_TYPE_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	m_uniformLocation[LAMBERT_MATERIAL_TYPE_FIXCOLOR] = glGetUniformLocation(programId, "uFixColor");
	Logger::GLError();
}

LambertMaterial::LambertMaterial(const vec4& color)
{
	SetColor(color);
}

LambertMaterial::LambertMaterial(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

void LambertMaterial::SetColor(const vec4& color)
{
	m_color = color;
	m_Type = LAMBERT_MATERIAL_TYPE_FIXCOLOR;
}

void LambertMaterial::SetTexture(shared_ptr<Texture> pTexture)
{
	m_pTexture = pTexture;
	m_Type = LAMBERT_MATERIAL_TYPE_TEXTURE;
}

bool LambertMaterial::Compare(IMaterial* pMaterial)
{
	auto pLambertMaterial = dynamic_cast<LambertMaterial*>(pMaterial);
	if (pLambertMaterial != nullptr)
	{
		if (m_Type == pLambertMaterial->ColorType())
		{
			return true;
		}
	}

	return false;
}
shared_ptr<IShaderCode> LambertMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		VERTEX_LAYOUT outLayout = VERTEX_LAYOUT_NONE;
		if (m_Type == LAMBERT_MATERIAL_TYPE_VERTEXCOLOR)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_COLOR);
		}
		else if (m_Type == LAMBERT_MATERIAL_TYPE_TEXTURE)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_TEXCOORD);
		}
		else if(m_Type == LAMBERT_MATERIAL_TYPE_FIXCOLOR)
		{
			outLayout = VERTEX_LAYOUT_NORMAL;
		}
		else
		{
			assert(0);
		}

		return make_shared<DefaultVertexCode>(outLayout);

	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<LambertMaterialFragCode>(m_Type);
	}
	else
	{
		return nullptr;
	}
}

bool LambertMaterial::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetMaterial = dynamic_cast<LambertMaterial*>(pTarget);
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