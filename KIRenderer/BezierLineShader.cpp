namespace KI
{
namespace Renderer
{

BezierLineShader::BezierLineShader()
{
}

BezierLineShader::~BezierLineShader()
{
}

void BezierLineShader::Initialize()
{
	FetchUniformLocation();
}

void BezierLineShader::FetchUniformLocation()
{
	m_uniformLocation.resize(BEZIERLINE_UNIFORM_NUM);
	m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] = glGetUniformLocation(m_programId, "numStrip");
	m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] = glGetUniformLocation(m_programId, "numSegment");
	Logger::GLError();
}

void BezierLineShader::Bind(shared_ptr<IUniform> uniform)
{
	if (m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM] == -1 ||
		m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM] == -1)
	{
		assert(0);
		return;
	}

	if (uniform->Type() != SHADER_TYPE::SHADER_TYPE_BEZIERLINE)
	{
		assert(0);
		return;
	}
	
	auto uniformParameter = static_pointer_cast<BezierLineUniform>(uniform);
	
	IShader::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_STRIP_NUM], uniformParameter->StripNum());
	IShader::BindInt(m_uniformLocation[BEZIERLINE_UNIFORM_SEGMENT_NUM],uniformParameter->SegmentNum());
}

void BezierLineShader::UnBind(shared_ptr<IUniform> uniform)
{

}}
}