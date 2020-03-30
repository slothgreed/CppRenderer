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

}
}