#ifndef PICK_MANAGER_H
#define PICK_MANAGER_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT PickManager
{
public:
	PickManager();
	~PickManager();

	void AddPickObject(shared_ptr<IPickable> pPickObject);
	void SetPickID();

	void Dispose();
private:
	vector<shared_ptr<IPickable>> m_pPickObjects;
};


}
}
#endif
