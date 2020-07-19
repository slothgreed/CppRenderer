namespace KI
{
namespace ShaderLib
{
ShaderStruct::ShaderStruct()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_STRUCT))
{
}

ShaderStruct::~ShaderStruct()
{
}

void ShaderStruct::Initialize(GLuint programId)
{
	BindScene(programId);
	BindLight(programId);
	BindMaterial(programId);
	BindModel(programId);
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

void ShaderStruct::BindMaterial(GLuint programId)
{
	GLint sceneBlock = glGetUniformBlockIndex(programId, "MaterialData");
	glUniformBlockBinding(programId, sceneBlock, MATERIAL_DATA_LOCATION);
	Logger::GLError();
}

void ShaderStruct::BindModel(GLuint programId)
{
	GLint lightBlock = glGetUniformBlockIndex(programId, "ModelData");
	glUniformBlockBinding(programId, lightBlock, MODEL_DATA_LOCATION);
	Logger::GLError();
}

void ShaderStruct::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{

}

void ShaderStruct::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{

}
}
}