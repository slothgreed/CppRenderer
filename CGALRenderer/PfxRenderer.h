#ifndef PFX_RENDERER_H
#define PFX_RENDERER_H

namespace KI
{

class PfxRenderer
{
public:
	PfxRenderer();
	~PfxRenderer();

	void AddPostEffect(shared_ptr<IPostEffect> postEffect);
	IPostEffect* FindPostEffect(PFX_TYPE type);
	void Draw();
private:
	
	vector<shared_ptr<IPostEffect>> m_pPfxLists;
};
}

#endif PFX_RENDERER_H
