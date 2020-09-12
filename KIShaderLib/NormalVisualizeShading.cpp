namespace KI
{
namespace ShaderLib
{

NormalVisualizeGeomCode::NormalVisualizeGeomCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_NORMALVIS) +
		string(SHADER_EXT_GEOM))
{
}

NormalVisualizeGeomCode::~NormalVisualizeGeomCode()
{
}

void NormalVisualizeGeomCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(NORMAL_VISUALIZE_UNIFORM_NUM);
	m_uniformLocation[NORMAL_VISUALIZE_UNIFORM_LENGTH] = glGetUniformLocation(programId, "uLength");
}

void NormalVisualizeGeomCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<NormalVisualizeShading*>(pShaderChunk.get());
	if (pShading == nullptr)
	{
		return;
	}

	BindLength(pShading->GetLength());
}

void NormalVisualizeGeomCode::BindLength(float length)
{
	if (m_uniformLocation[NORMAL_VISUALIZE_UNIFORM_LENGTH] == -1)
	{
		assert(0);
		return;
	}

	IShaderCode::BindFloat(m_uniformLocation[NORMAL_VISUALIZE_UNIFORM_LENGTH], length);
}

bool NormalVisualizeGeomCode::Compare(IShaderCode* pShaderCode)
{
	auto pShading = dynamic_cast<NormalVisualizeGeomCode*>(pShaderCode);
	if (pShading != nullptr)
	{
		return true;
	}

	return false;
}

bool NormalVisualizeShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetBuffer = dynamic_cast<NormalVisualizeShading*>(pTarget);
	if (pTargetBuffer == nullptr)
	{
		return false;
	}

	return true;
}

NormalVisualizeShading::NormalVisualizeShading()
{
	m_pShading = make_shared<BasicShading>(vec4(1,0,0,1));
}

shared_ptr<IShaderCode> NormalVisualizeShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		auto pCode = m_pShading->NewShaderCode(pBuildInfo, type);
		((DefaultVertexCode*)pCode.get())->SetShaderDefine(VERTEX_LAYOUT_NORMAL);
		((DefaultVertexCode*)pCode.get())->SetPlanePosition(true);
		return pCode;
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return m_pShading->NewShaderCode(pBuildInfo, type);
	}
	else if (type == SHADER_PROGRAM_GEOM)
	{
		return make_shared<NormalVisualizeGeomCode>();
	}

	return false;
}

}
}