namespace KI
{
namespace ShaderLib
{


PickFragCode::PickFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_PICK) +
		string(SHADER_EXT_FRAG))
{
}

PickFragCode::~PickFragCode()
{
}

void PickFragCode::GetDefineCode(string& code)
{
}

bool PickFragCode::Compare(IShaderCode* pShaderCode)
{
	return true;
}

void PickFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
}

void PickFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
}

void PickFragCode::Initialize(GLuint programId)
{
}

PickShading::PickShading()
{
}

shared_ptr<IShaderCode> PickShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		return make_shared<DefaultVertexCode>(VERTEX_LAYOUT_NONE);
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<PickFragCode>();
	}
	else
	{
		return nullptr;
	}
}

bool PickShading::NewShaderCompare(IShaderChunk* pTarget)
{
	return true;
}
}
}