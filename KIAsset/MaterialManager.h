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
	shared_ptr<IMaterial> GetSystemMaterial(SYSTEM_MATERIAL type);

private:
	void CreateSystemMaterial();
	map<SYSTEM_MATERIAL, shared_ptr<IMaterial>> m_pMaterials;
	static MaterialManager* m_Instance;

};

}
}

#endif MATERIAL_MANAGER_H