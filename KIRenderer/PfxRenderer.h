#ifndef PFX_RENDERER_H
#define PFX_RENDERER_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT PfxRenderer : IXMLIO
{
public:
	PfxRenderer();
	~PfxRenderer();

	void AddPostEffect(shared_ptr<IPostEffect> postEffect);
	IPostEffect* FindPostEffect(int index);
	IPostEffect* FindPostEffect(PFX_TYPE type);
	int PostEffectNum();
	void Draw();
	void Resize(int width, int height);

	//virtual void ReadFromXML(const boost::property_tree::ptree& tree);
	//virtual void WriteToXML(const boost::property_tree::ptree& tree);
private:
	
	vector<shared_ptr<IPostEffect>> m_pPfxLists;
};
}
}
#endif PFX_RENDERER_H
