namespace KI
{
namespace ShaderLib
{
GrayScaleFragCode::GrayScaleFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_GRAYSCALE) +
		string(SHADER_EXT_FRAG))
{
}

GrayScaleFragCode::~GrayScaleFragCode()
{
}

void GrayScaleFragCode::Initialize(GLuint programId)
{
	FetchUniformLocation(programId);
}

void GrayScaleFragCode::FetchUniformLocation(GLuint programId)
{
	m_uniformLocation.resize(GRAYSCALE_UNIFORM_NUM);
	m_uniformLocation[GRAYSCALE_UNIFORM_SOURCE_TEXTURE] = glGetUniformLocation(programId, "uTexture0");
	Logger::GLError();
}

void GrayScaleFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<GrayScaleShading*>(pShaderChunk.get());
	if (pShading == nullptr)
	{
		return;
	}

	pShading->GetTexture()->Begin();
	BindColorTexture();
}

void GrayScaleFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<GrayScaleShading*>(pShaderChunk.get());
	if (pShading == nullptr)
	{
		return;
	}
	pShading->GetTexture()->End();
}

bool GrayScaleShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetBuffer = dynamic_cast<GrayScaleShading*>(pTarget);
	if (pTargetBuffer == nullptr)
	{
		return false;
	}

	return true;
}

shared_ptr<IShaderCode> GrayScaleShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (SHADER_PROGRAM_VERTEX == type)
	{
		return make_shared<PostProcessVertexCode>();
	}
	else if(SHADER_PROGRAM_FRAG == type)
	{
		return make_shared<GrayScaleFragCode>();
	}
	else
	{
		return nullptr;
	}
}

void GrayScaleFragCode::BindColorTexture()
{
	if (m_uniformLocation[GRAYSCALE_UNIFORM_SOURCE_TEXTURE] == -1)
	{
		assert(0);
	}

	IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[GRAYSCALE_UNIFORM_SOURCE_TEXTURE]);
}
}
}