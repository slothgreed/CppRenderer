namespace KI
{
namespace Renderer
{

void OutputFragCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(UNIFORM_LOCATION_NUM);
	m_uniformLocation[UNIFORM_LOCATION_COLOR_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	Logger::GLError();
}
bool OutputFragCode::Compare(IShaderCode* pShaderCode)
{
	return true;
}
void OutputFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pShading = static_pointer_cast<OutputShading>(pShaderChunk);
	if (pShading == nullptr)
	{
		assert(0);
		return;
	}

	pShading->GetTexture()->Begin();
	IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[UNIFORM_LOCATION_COLOR_TEXTURE]);
}

void OutputFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pShading = static_pointer_cast<OutputShading>(pShaderChunk);
	if (pShading == nullptr)
	{
		assert(0);
		return;
	}

	pShading->GetTexture()->End();
}

OutputShading::~OutputShading()
{
}

OutputShading::OutputShading(shared_ptr<Texture> pTexture)
{
	SetTexture(pTexture);
}

bool OutputShading::Compare(IShading* pShading)
{
	auto pOutputShading = dynamic_cast<OutputShading*>(pShading);
	if (pOutputShading == nullptr)
	{
		return false;
	}

	return true;
}

bool OutputShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pOutputShading = dynamic_cast<OutputShading*>(pTarget);
	return Compare(pOutputShading);
}

shared_ptr<IShaderCode> OutputShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		return make_shared<PostProcessVertexCode>();
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<OutputFragCode>();
	}

	return nullptr;
}
}
}
