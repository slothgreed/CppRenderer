#ifndef PFX_PLANE_H
#define PFX_PLANE_H

namespace KI
{
class PfxPlane
{
public:
	PfxPlane(shared_ptr<IMaterial> material);
	~PfxPlane();
	void Initialize();
	void Draw();
private:
	shared_ptr<IMaterial> m_pMaterial;
};

}
#endif PFX_PLANE_H