namespace KI
{
namespace Renderer
{

BezierLineTCSCode::BezierLineTCSCode()
	:IShaderCode(
	string(SHADER_DIRECTORY) +
	string(SHADER_BEZIERLINE) +
	string(SHADER_EXT_TCS))
{
}

BezierLineTCSCode::~BezierLineTCSCode()
{

}

void BezierLineTCSCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(BEZIERLINE_UNIFORM_NUM);
	m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] = glGetUniformLocation(programId, "numStrips");
	m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] = glGetUniformLocation(programId, "numSegments");
	Logger::GLError();
}



void BezierLineTCSCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = dynamic_cast<BezierLineMaterial*>(pShaderChunk.get());
	if (pMaterial->GetPatchVertices() == 0)
	{
		assert(0);
		return;
	}

	glPatchParameteri(GL_PATCH_VERTICES, pMaterial->GetPatchVertices());

	if (m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] == -1 ||
		m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] == -1)
	{
		assert(0);
		return;
	}

	IShaderCode::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM], pMaterial->StripNum());
	IShaderCode::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM], pMaterial->SegmentNum());
	
}

void BezierLineTCSCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{

}

void BezierLineMaterial::SetPatchVertices(GLuint patchVertex)
{
	m_patchVertex = patchVertex;
}

bool BezierLineMaterial::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetBuffer = dynamic_cast<BezierLineMaterial*>(pTarget);
	if (pTargetBuffer == nullptr)
	{
		return false;
	}

	return true;
}

shared_ptr<IShaderCode> BezierLineMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	switch (type)
	{
	case SHADER_PROGRAM_VERTEX:
		return make_shared<DefaultVertexCode>(pBuildInfo->GetVertexBuffer().get());
	case SHADER_PROGRAM_FRAG:
		return make_shared<BasicMaterialFragCode>(BASIC_MATERIAL_TYPE::BASIC_COLOR_TYPE_FIXCOLOR);
	case SHADER_PROGRAM_TCS:
		return make_shared<BezierLineTCSCode>();
	case SHADER_PROGRAM_TESS:
		return make_shared<BezierLineTESCode>();
	default:
		return nullptr;
	}

	return nullptr;
}
}
}