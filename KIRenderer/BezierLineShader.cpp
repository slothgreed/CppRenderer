namespace KI
{
namespace Renderer
{

BezierLineShader::BezierLineShader()
{
	m_patchVertex = 0;
}

BezierLineShader::~BezierLineShader()
{

}

void BezierLineShader::Initialize()
{
	BindScene();
	FetchUniformLocation();
	
}

void BezierLineShader::SetPatchVertices(GLuint patchVertex)
{
	m_patchVertex = patchVertex;
}

void BezierLineShader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "SceneData");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}


void BezierLineShader::FetchUniformLocation()
{
	m_uniformLocation.resize(BEZIERLINE_UNIFORM_NUM);
	m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] = glGetUniformLocation(m_programId, "numStrips");
	m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] = glGetUniformLocation(m_programId, "numSegments");
	Logger::GLError();
}

void BezierLineShader::Bind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform)
{
	if (m_patchVertex == 0)
	{
		assert(0);
		return;
	}
	glPatchParameteri(GL_PATCH_VERTICES, m_patchVertex);

	if (m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] == -1 ||
		m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] == -1)
	{
		assert(0);
		return;
	}

	if (pUniform->TCS()->Type() != SHADER_TYPE::SHADER_TYPE_BEZIERLINE)
	{
		assert(0);
		return;
	}
	
	auto uniform = static_pointer_cast<BezierLineUniform>(pUniform->TCS());
	IShader::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM], uniform->StripNum());
	IShader::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM], uniform->SegmentNum());
	
}

void BezierLineShader::UnBind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> uniform)
{

}}
}