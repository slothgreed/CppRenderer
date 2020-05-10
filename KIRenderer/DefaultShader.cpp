namespace KI
{
namespace Renderer
{
DefaultShader::DefaultShader()
{
}

DefaultShader::~DefaultShader()
{
}

void DefaultShader::Initialize()
{
	BindScene();
	BindLight();
	FetchUniformLocation();
	
}

void DefaultShader::BindScene()
{
	GLint sceneBlock = glGetUniformBlockIndex(m_programId, "SceneData");
	glUniformBlockBinding(m_programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::BindLight()
{
	GLint lightBlock = glGetUniformBlockIndex(m_programId, "LightData");
	glUniformBlockBinding(m_programId, lightBlock, LIGHT_DATA_LOCATION);
	Logger::GLError();
}

void DefaultShader::FetchUniformLocation()
{

}

void DefaultShader::Bind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform)
{
	pMaterial->Bind();
}

void DefaultShader::UnBind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform)
{
	pMaterial->UnBind();
}

}
}