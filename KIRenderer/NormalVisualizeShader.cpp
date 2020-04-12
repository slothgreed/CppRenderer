namespace KI
{
namespace Renderer
{

NormalVisualizeShader::NormalVisualizeShader()
{
}

NormalVisualizeShader::~NormalVisualizeShader()
{
}

void NormalVisualizeShader::Initialize()
{
	BindScene();
	BindLight();
	FetchUniformLocation();
}

void NormalVisualizeShader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "SceneData");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void NormalVisualizeShader::BindLight()
{
	GLint lightBlock = glGetUniformBlockIndex(m_programId, "LightData");
	glUniformBlockBinding(m_programId, lightBlock, LIGHT_DATA_LOCATION);
	Logger::GLError();
}

void NormalVisualizeShader::FetchUniformLocation()
{
	m_uniformLocation.resize(NORMAL_VISUALIZE_UNIFORM_NUM);
	m_uniformLocation[NORMAL_VISUALIZE_UNIFORM_LENGTH] = glGetUniformLocation(m_programId, "uLength");
}

void NormalVisualizeShader::Bind(shared_ptr<UniformSet> pUniform)
{
	if (pUniform->Geometry()->Type() != SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE)
	{
		assert(0);
		return;
	}

	auto uniformParameter = static_pointer_cast<NormalVisualizeUniform>(pUniform->Geometry());

	BindLength(uniformParameter->Length());
}

void NormalVisualizeShader::BindLength(float length)
{
	if (m_uniformLocation[NORMAL_VISUALIZE_UNIFORM_LENGTH] == -1)
	{
		assert(0);
		return;
	}

	IShader::BindFloat(m_uniformLocation[NORMAL_VISUALIZE_UNIFORM_LENGTH], length);
}
}
}