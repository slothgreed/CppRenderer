namespace KI
{
namespace Renderer
{
SSLICFragCode::SSLICFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_SSLIC) +
		string(SHADER_EXT_FRAG))
{
}

SSLICFragCode::~SSLICFragCode()
{

}

void SSLICFragCode::Initialize(GLuint programId)
{
	m_uniformLocation.resize(SSLIC_UNIFORM_NUM);
	m_uniformLocation[SSLIC_UNIFORM_COLOR_TEXTURE] = glGetUniformLocation(programId, "uTexture0");

	Logger::GLError();
}


void SSLICFragCode::Bind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = static_pointer_cast<SSLICMaterial>(pShaderChunk);
	if (pMaterial == nullptr)
	{
		assert(0);
	}

	pMaterial->GetTexture()->Begin();
	IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[SSLIC_UNIFORM_COLOR_TEXTURE]);
}

void SSLICFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = static_pointer_cast<SSLICMaterial>(pShaderChunk);
	if (pMaterial == nullptr)
	{
		assert(0);
	}

	pMaterial->GetTexture()->End();
}

shared_ptr<IShaderCode> SSLICMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		return make_shared<PostProcessVertexCode>();
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<SSLICFragCode>();
	}
	else
	{
		return nullptr;
	}
}
}
}