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
	auto pMaterial = static_pointer_cast<OutputMaterial>(pShaderChunk);
	if (pMaterial == nullptr)
	{
		assert(0);
		return;
	}

	pMaterial->GetTexture()->Begin();
	IShaderCode::BindTexture(GL_TEXTURE0, m_uniformLocation[UNIFORM_LOCATION_COLOR_TEXTURE]);
}

void OutputFragCode::UnBind(shared_ptr<IShaderChunk> pShaderChunk)
{
	auto pMaterial = static_pointer_cast<OutputMaterial>(pShaderChunk);
	if (pMaterial == nullptr)
	{
		assert(0);
		return;
	}

	pMaterial->GetTexture()->End();
}

OutputMaterial::~OutputMaterial()
{
}

bool OutputMaterial::Compare(IMaterial* pMaterial)
{
	auto pOutputMaterial = dynamic_cast<OutputMaterial*>(pMaterial);
	if (pOutputMaterial == nullptr)
	{
		return false;
	}

	return true;
}

shared_ptr<IShaderCode> OutputMaterial::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
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
