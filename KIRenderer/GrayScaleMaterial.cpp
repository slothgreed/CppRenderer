namespace KI
{
namespace Renderer
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

void GrayScaleFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = dynamic_cast<GrayScaleMaterial*>(pShaderChunk.get());
	if (pMaterial == nullptr)
	{
		return;
	}

	pMaterial->GetTexture()->Begin();
	BindColorTexture();
}

void GrayScaleFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = dynamic_cast<GrayScaleMaterial*>(pShaderChunk.get());
	if (pMaterial == nullptr)
	{
		return;
	}
	pMaterial->GetTexture()->End();
}

bool GrayScaleMaterial::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pTargetBuffer = dynamic_cast<GrayScaleMaterial*>(pTarget);
	if (pTargetBuffer == nullptr)
	{
		return false;
	}

	return true;
}

shared_ptr<IShaderCode> GrayScaleMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
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