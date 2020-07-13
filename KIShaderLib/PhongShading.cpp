namespace KI
{
namespace ShaderLib
{

PhongShadingFragCode::PhongShadingFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_PHONGSHADING) +
		string(SHADER_EXT_FRAG))
{
}

PhongShadingFragCode::~PhongShadingFragCode()
{

}

PhongShading::PhongShading(PHONG_SHADING_TYPE type, const ADSShadingData& data)
{
	m_Type = type;
	Set(data);
}

PhongShading::~PhongShading()
{
}

void PhongShading::Set(const ADSShadingData& adsData)
{
	m_ADSData = adsData;
}


}
}