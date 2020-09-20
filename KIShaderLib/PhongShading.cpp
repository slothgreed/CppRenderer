namespace KI
{
namespace ShaderLib
{

PhongShadingFragCode::PhongShadingFragCode(PHONG_SHADING_TYPE type, SHADING_COLOR_TYPE colorType, const MaterialData& data)
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_PHONGSHADING) +
		string(SHADER_EXT_FRAG))
{
	m_Type = type;
	m_pColorCode = make_shared<GetColorCode>(colorType);
	m_Material = data;
}

PhongShadingFragCode::~PhongShadingFragCode()
{

}

void PhongShadingFragCode::GetDefineCode(string& code)
{
	m_pColorCode->GetDefineCode(code);
	if (m_Type == PHONG_SHADING_TYPE::PHONG_SHADING_TYPE_BLIN)
	{
		code += "#define PHONG_BLIN\n";
	}
	else if (m_Type == PHONG_SHADING_TYPE::PHONG_SHADING_TYPE_COOKTRANCE)
	{
		code += "#define PHONG_COOKTRANCE\n";
	}
	else if (m_Type == PHONG_SHADING_TYPE::PHONG_SHADING_TYPE_PHONG)
	{
		code += "#define PHONG_PHONG\n";
	}
	else
	{
		assert(0);
		code += "#define IN_COLOR\n";
	}
}

bool PhongShadingFragCode::Compare(IShaderCode* pShaderCode)
{
	auto pCode = dynamic_cast<PhongShadingFragCode*>(pShaderCode);
	if (pCode == nullptr)
	{
		return false;
	}

	if (pCode->m_Type != m_Type)
	{
		return false;
	}

	return pCode->m_pColorCode->Compare(m_pColorCode.get());
}

void PhongShadingFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform)
{
	m_pColorCode->Bind(pShaderChunk, pUniform);

	auto pUniformStruct = dynamic_cast<UniformStruct*>(pUniform.get());
	if (pUniformStruct == nullptr)
	{
		assert(0);
		return;
	}

	if (pUniformStruct->GetMaterial() != nullptr)
	{
		pUniformStruct->GetMaterial()->Set(m_Material);
		pUniformStruct->GetMaterial()->Bind();
	}
}

void PhongShadingFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform)
{
	m_pColorCode->UnBind(pShaderChunk, pUniform);
	auto pUniformStruct = dynamic_cast<UniformStruct*>(pUniform.get());
	if (pUniformStruct == nullptr)
	{
		assert(0);
		return;
	}

	if (pUniformStruct->GetMaterial() != nullptr)
	{
		pUniformStruct->GetMaterial()->UnBind();
	}
}

void PhongShadingFragCode::Initialize(GLuint programId)
{
	m_pColorCode->Initialize(programId);
}


PhongShading::PhongShading(PHONG_SHADING_TYPE type, SHADING_COLOR_TYPE colorType, const ADSMaterial& data)
{
	m_Type = type;
	m_ColorType = colorType;
	Set(data);
}

PhongShading::~PhongShading()
{
}

void PhongShading::Set(const ADSMaterial& adsMaterial)
{
	m_ADSMaterial = adsMaterial;
}

bool PhongShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pPhongShading = dynamic_cast<PhongShading*>(pTarget);
	if (pPhongShading == nullptr)
	{
		return false;
	}

	if (pPhongShading->m_Type == m_Type)
	{
		return true;
	}

	return false;
}
shared_ptr<IShaderCode> PhongShading::NewShaderCode(IShaderBuildInfo* pBuildInfo, SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		VERTEX_LAYOUT outLayout = VERTEX_LAYOUT_NONE;
		if (m_ColorType == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_VERTEXCOLOR)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_COLOR);
		}
		else if (m_ColorType == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_TEXTURE)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL | VERTEX_LAYOUT_TEXCOORD);
		}
		else if (m_ColorType == SHADING_COLOR_TYPE::SHADING_COLOR_TYPE_FIXCOLOR)
		{
			outLayout = (VERTEX_LAYOUT)(VERTEX_LAYOUT_POSITION | VERTEX_LAYOUT_NORMAL);
		}
		else
		{
			assert(0);
		}

		auto pCode = make_shared<DefaultVertexCode>(outLayout);
		pCode->SetWorldOutPosition(true);
		return pCode;
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		MaterialData material;
		material.ambient = m_ADSMaterial.GetAmbient();
		material.diffuse = m_ADSMaterial.GetDiffuse();
		material.specular = m_ADSMaterial.GetSpecular();
		material.shining = m_ADSMaterial.GetShinning();
		return make_shared<PhongShadingFragCode>(m_Type, m_ColorType, material);
	}
	else
	{
		return nullptr;
	}
}


}
}