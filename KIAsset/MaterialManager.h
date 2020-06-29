#ifndef SHADING_MANAGER_H
#define SHADING_MANAGER_H
// todo : ˆÚ“®
namespace KI
{
namespace Asset
{

enum SYSTEM_SHADING
{
	SYSTEM_SHADING_SELECTION,
	SYSTEM_SHADING_NUM
};
class DLL_EXPORT ShadingManager
{
public:
	ShadingManager();
	~ShadingManager();
	static ShadingManager* Instance();

	void Initialize();
	shared_ptr<IShading> GetSystemShading(SYSTEM_SHADING type);

private:
	void CreateSystemShading();
	map<SYSTEM_SHADING, shared_ptr<IShading>> m_pShadings;
	static ShadingManager* m_Instance;

};

}
}

#endif SHADING_MANAGER_H