namespace KI
{
namespace ShaderLib
{

void TangentVisualizeVertexCode::GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes)
{
	pShaderCodes.push_back(make_shared<ShaderCommon>());
	pShaderCodes.push_back(make_shared<ShaderStruct>());
}
TangentVisualizeGeomCode::TangentVisualizeGeomCode(bool visibleNormal)
	:m_visibleNormal(visibleNormal),
	IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_TANGENTVIS) +
		string(SHADER_EXT_GEOM))
{
}

TangentVisualizeGeomCode::~TangentVisualizeGeomCode()
{
}

void TangentVisualizeGeomCode::GetDefineCode(string& code)
{
	if (m_visibleNormal) {
		code += "#define VISIBLE_NORMAL\n";
	}
}

void TangentVisualizeGeomCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(TANGENT_VISUALIZE_UNIFORM_NUM);
	m_uniformLocation[TANGENT_VISUALIZE_UNIFORM_LENGTH] = glGetUniformLocation(programId, "uLength");
	m_uniformLocation[TANGENT_VISUALIZE_UNIFORM_OFFSET] = glGetUniformLocation(programId, "uOffset");
}

void TangentVisualizeGeomCode::Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<TangentVisualizeShading*>(pShaderChunk.get());
	if (pShading == nullptr)
	{
		return;
	}

	BindLength(pShading->GetLength());
	BindOffset(pShading->GetOffset());
}

void TangentVisualizeGeomCode::BindLength(float length)
{
	if (m_uniformLocation[TANGENT_VISUALIZE_UNIFORM_LENGTH] == -1)
	{
		assert(0);
		return;
	}

	IShaderCode::BindFloat(m_uniformLocation[TANGENT_VISUALIZE_UNIFORM_LENGTH], length);
}

void TangentVisualizeGeomCode::BindOffset(float offset)
{
	if (m_uniformLocation[TANGENT_VISUALIZE_UNIFORM_LENGTH] == -1)
	{
		assert(0);
		return;
	}

	IShaderCode::BindFloat(m_uniformLocation[TANGENT_VISUALIZE_UNIFORM_OFFSET], offset);
}

bool TangentVisualizeGeomCode::Compare(IShaderCode* pShaderCode)
{
	auto pShading = dynamic_cast<TangentVisualizeGeomCode*>(pShaderCode);
	if (pShading != nullptr)
	{
		return true;
	}

	return false;
}

bool TangentVisualizeShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetBuffer = dynamic_cast<TangentVisualizeShading*>(pTarget);
	if (pTargetBuffer == nullptr)
	{
		return false;
	}

	if (GetVisualizeNormal() == pTargetBuffer->GetVisualizeNormal()) {
		return false;
	}

	return true;
}

TangentVisualizeShading::~TangentVisualizeShading()
{
}

TangentVisualizeShading::TangentVisualizeShading(vec4 color, bool visibleNormal)
{
	m_pShading = make_shared<BasicShading>(color);
	m_visibleNormal = visibleNormal;
}

shared_ptr<IShaderCode> TangentVisualizeShading::NewShaderCode(IShaderBuildInfo* pBuildInfo, SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		return make_shared<TangentVisualizeVertexCode>();
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return m_pShading->NewShaderCode(pBuildInfo, type);
	}
	else if (type == SHADER_PROGRAM_GEOM)
	{
		return make_shared<TangentVisualizeGeomCode>(m_visibleNormal);
	}

	return false;
}

void TangentVisualizeShading::SetColor(const vec4& color)
{
	auto pShading = dynamic_cast<BasicShading*>(m_pShading.get());
	if (pShading) {
		pShading->SetColor(color);
	}
}

}
}