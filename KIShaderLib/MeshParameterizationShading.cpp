namespace KI
{
namespace ShaderLib
{

MeshParameterizationVertCode::MeshParameterizationVertCode()
	:IShaderCode(
		string(SHADER_DIRECTORY)+
		string(SHADER_MESH_PARAM)+
		string(SHADER_EXT_VERTEX))
{
}
MeshParameterizationFragCode::MeshParameterizationFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_MESH_PARAM) +
		string(SHADER_EXT_FRAG))
{
}

MeshParameterizationGeomCode::MeshParameterizationGeomCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_MESH_PARAM) +
		string(SHADER_EXT_GEOM))
{
}

void MeshParameterizationGeomCode::GetIncludeCode(vector<shared_ptr<IShaderCode>>& pShaderCodes)
{
	pShaderCodes.push_back(make_shared<ShaderStruct>());
}

MeshParameterizationGeomCode::~MeshParameterizationGeomCode()
{
}

void MeshParameterizationGeomCode::Initialize(GLuint programId)
{
}

void MeshParameterizationGeomCode::Bind(shared_ptr<IShaderChunk> pShaderChunk,shared_ptr<IUniformStorage> pUniform)
{
	auto pShading = dynamic_cast<MeshParameterizationShading*>(pShaderChunk.get());
	if (pShading == nullptr)
	{
		return;
	}

}


bool MeshParameterizationGeomCode::Compare(IShaderCode* pShaderCode)
{
	auto pShading = dynamic_cast<MeshParameterizationGeomCode*>(pShaderCode);
	if (pShading != nullptr)
	{
		return true;
	}

	return false;
}

bool MeshParameterizationShading::NewShaderCompare(IShaderChunk* pTarget)
{
	auto pShading = dynamic_cast<MeshParameterizationShading*>(pTarget);
	if (pShading == nullptr)
	{
		return false;
	}

	return true;
}

MeshParameterizationShading::MeshParameterizationShading()
{
}

shared_ptr<IShaderCode> MeshParameterizationShading::NewShaderCode(IShaderBuildInfo* pBuildInfo,SHADER_PROGRAM_TYPE type)
{
	if (type == SHADER_PROGRAM_VERTEX)
	{
		return make_shared<MeshParameterizationVertCode>();
	}
	else if (type == SHADER_PROGRAM_FRAG)
	{
		return make_shared<MeshParameterizationFragCode>();
	}
	else if (type == SHADER_PROGRAM_GEOM)
	{
		return make_shared<MeshParameterizationGeomCode>();
	}

	return false;
}

}
}