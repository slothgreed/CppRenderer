namespace KI
{
namespace Gfx
{
IShaderBuildInfo::IShaderBuildInfo(SHADER_TYPE type)
{
	m_type = type;
}

IShaderBuildInfo::~IShaderBuildInfo()
{
}

bool IShaderBuildInfo::Compare(IShaderBuildInfo* pShaderBuildInfo)
{
	for (int i = 0; i < SHADER_PROGRAM_NUM; i++)
	{
		auto shaderType = (SHADER_PROGRAM_TYPE)i;
		if (GetShaderCode(shaderType) == nullptr &&
			pShaderBuildInfo->GetShaderCode(shaderType) == nullptr)
		{
			continue;
		}

		if (GetShaderCode(shaderType) != nullptr && pShaderBuildInfo->GetShaderCode(shaderType) != nullptr)
		{
			if (!GetShaderCode(shaderType)->Compare(pShaderBuildInfo->GetShaderCode(shaderType).get()))
			{
				return false;
			}
		}
		else
		{
			return false;
		}

	}

	return true;
}

}
}