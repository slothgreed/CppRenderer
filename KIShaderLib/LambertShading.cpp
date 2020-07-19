namespace KI
{
namespace ShaderLib
{


LambertFragCode::LambertFragCode(SHADING_COLOR_TYPE type)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_LAMBERTSHADING) +
		string(SHADER_EXT_FRAG))
{
	m_pColorCode = make_shared<GetColorCode>(type);
}

LambertFragCode::~LambertFragCode()
{
}

void LambertFragCode::GetDefineCode(string& code)
{
	m_pColorCode->GetDefineCode(code);
}

bool LambertFragCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<LambertFragCode*>(pShaderCode);
	if (pCode == nullptr)
	{
		return false;
	}

	return pCode->m_pColorCode->Compare(m_pColorCode.get());
}

void LambertFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	m_pColorCode->Bind(pShaderChunk, pUniform);
}

void LambertFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	m_pColorCode->UnBind(pShaderChunk, pUniform);
}

void LambertFragCode::Initialize(GLuint programId)
{
	m_pColorCode->Initialize(programId);
}

LambertShading::LambertShading(const vec4& color)
{
	SetColor(color);
}

LambertShading::LambertShading(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

bool LambertShading::Compare(IShading* pShading)
{
	auto pLambertShading = dynamic_cast<LambertShading*>(pShading);
	if (pLambertShading != nullptr)
	{
		if (ColorType() == pLambertShading->ColorType())
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
		if (ColorType() == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_VERTEXCOLOR)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_COLOR);
		}
		else if (ColorType() == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_TEXTURE)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_TEXCOORD);
		}
		else if(ColorType() == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_FIXCOLOR)
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
		return make_shared<LambertFragCode>(ColorType());
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