namespace KI
{
namespace Renderer
{
ShaderStruct::ShaderStruct()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_BASICMATERIAL) +
		string(SHADER_EXT_VERTEX))
{
}

ShaderStruct::~ShaderStruct()
{
}

void ShaderStruct::Initialize(GLuint programId)
{
	BindScene(programId);
	BindLight(programId);
}

void ShaderStruct::BindScene(GLuint programId)
{
	GLint sceneBlock = glGetUniformBlockIndex(programId, "SceneData");
	glUniformBlockBinding(programId, sceneBlock, SCENE_DATA_LOCATION);
	Logger::GLError();
}

void ShaderStruct::BindLight(GLuint programId)
{
	GLint lightBlock = glGetUniformBlockIndex(programId, "LightData");
	glUniformBlockBinding(programId, lightBlock, LIGHT_DATA_LOCATION);
	Logger::GLError();
}

}
}