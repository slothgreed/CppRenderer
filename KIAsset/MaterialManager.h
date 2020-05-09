#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H
// todo : ˆÚ“®
namespace KI
{
namespace Asset
{

enum SYSTEM_MATERIAL
{
	SYSTEM_MATERIAL_SELECTION,
	SYSTEM_MATERIAL_NUM
};
class DLL_EXPORT MaterialManager
{
public:
	MaterialManager();
	~MaterialManager();
	static MaterialManager* Instance();

	void Initialize();
	shared_ptr<IShaderPass> GetSystemShaderPass(SYSTEM_MATERIAL systemShaderPass);

private:
	void CreateSystemShaderPass();
	map<SYSTEM_MATERIAL, shared_ptr<IShaderPass>> m_pShaderPasss;
	static MaterialManager* m_Instance;

};

}
}

#endif MATERIAL_MANAGER_H