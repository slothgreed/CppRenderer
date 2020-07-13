#ifndef UNIFORM_STRUCT_H
#define UNIFORM_STRUCT_H

namespace KI
{
namespace ShaderLib
{
class DLL_EXPORT UniformStruct : public IUniformStorage
{
public:
	UniformStruct() {};
	~UniformStruct() {};

	void SetLight(shared_ptr<UniformLight> value) { m_pLight = value; };
	void SetScene(shared_ptr<UniformScene> value) { m_pScene = value; };
	void SetModel(shared_ptr<UniformModel> value) { m_pModel = value; };
	void SetMaterial(shared_ptr<UniformMaterial> value) { m_pMaterial = value; };
	shared_ptr<UniformLight> GetLight() { return m_pLight; };
	shared_ptr<UniformScene> GetScene() { return m_pScene; };
	shared_ptr<UniformModel> GetModel() { return m_pModel; };
	shared_ptr<UniformMaterial> GetMaterial() { return m_pMaterial; };
private:
	shared_ptr<UniformLight> m_pLight;
	shared_ptr<UniformMaterial> m_pMaterial;
	shared_ptr<UniformScene> m_pScene;
	shared_ptr<UniformModel> m_pModel;
};
}
}
#endif UNIFORM_STRUCT_H
