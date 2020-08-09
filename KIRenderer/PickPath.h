#ifndef PICK_PATH_H
#define	PICK_PATH_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT PickPath
{
public:
	PickPath();
	~PickPath();

	void Initialize(int width, int height);
	void Resize(int width, int height);
	void Draw(shared_ptr<Scene> pScene);
	void ResetPickID(vector<shared_ptr<IGLPick>>& modelNodes);
private:
	shared_ptr<IShader> m_pPickShader;
	shared_ptr<RenderTarget> m_pRenderTarget;
};
}
}


#endif PICK_PATH_H