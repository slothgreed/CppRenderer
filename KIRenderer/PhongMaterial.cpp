namespace KI
{
namespace Renderer
{

PhongMaterialFragCode::PhongMaterialFragCode()
	:IShaderCode(
		string(SHADER_DIRECTORY) +
		string(SHADER_PHONGMATERIAL) +
		string(SHADER_EXT_FRAG))
{
}

PhongMaterialFragCode::~PhongMaterialFragCode()
{

}

PhongMaterial::PhongMaterial(PHONG_MATERIAL_TYPE type, const ADSMaterialData& data)
{
	m_Type = type;
	Set(data);
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::Set(const ADSMaterialData& adsData)
{
	m_ADSData = adsData;
}


}
}