#ifndef PICK_PATH_H
#define	PICK_PATH_H

namespace KI
{
namespace Asset
{

class DLL_EXPORT PickPath
{
public:
	PickPath();
	~PickPath();

	void Initialize(int width, int height);
	void Resize(int width, int height);
	void Draw(const vector<shared_ptr<IModelNode>>& modelNodes);
	void ResetPickID(const vector<shared_ptr<IModelNode>> modelNodes);
private:
	shared_ptr<IShader> m_pPickShader;
	shared_ptr<RenderTarget> m_pRenderTarget;
};
}
}


#endif PICK_PATH_H