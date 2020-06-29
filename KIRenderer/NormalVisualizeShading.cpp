namespace KI
{
namespace Renderer
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

void NormalVisualizeGeomCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
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
shared_ptr<IShaderCode> NormalVisualizeShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		auto pCode = make_shared<DefaultVertexCode>(pBuildInfo->GetVertexBuffer().get());
		pCode->SetPlanePosition(true);
		return pCode;
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<BasicFragCode>(BASIC_SHADING_TYPE::BASIC_SHADING_TYPE_FIXCOLOR);
	}
	else if (type == SHADER_PROGRAM_GEOM)
	{
		return make_shared<NormalVisualizeGeomCode>();
	}

	return false;
}

}
}