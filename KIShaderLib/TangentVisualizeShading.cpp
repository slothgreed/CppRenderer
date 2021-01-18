namespace KI
{
namespace ShaderLib
{


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
}

void TangentVisualizeGeomCode::Bind(shared_ptr<IShaderChunk> pShaderChunk, shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<NormalVisualizeShading*>(pShaderChunk.get());
	if (pShading == nullptr)
	{
		return;
	}

	BindLength(pShading->GetLength());
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
		auto pCode = m_pShading->NewShaderCode(pBuildInfo, type);
		// –@ü‚Å‘ã—p‚µ‚Ä‚¨‚­B
		((DefaultVertexCode*)pCode.get())->SetShaderDefine(VERTEX_LAYOUT_NORMAL);
		((DefaultVertexCode*)pCode.get())->SetPlaneGLPosition(true);
		return pCode;
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return m_pShading->NewShaderCode(pBuildInfo, type);
	}
	else if (type == SHADER_PROGRAM_GEOM)
	{
		return make_shared<TangentVisualizeGeomCode>();
	}

	return false;
}

}
}