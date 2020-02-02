#ifndef PFX_RENDERER_H
#define PFX_RENDERER_H

namespace KI
{

class PfxRenderer : IXMLIO
{
public:
	PfxRenderer();
	~PfxRenderer();

	void AddPostEffect(shared_ptr<IPostEffect> postEffect);
	IPostEffect* FindPostEffect(PFX_TYPE type);
	void Draw();

	virtual void ReadFromXML(const boost::property_tree::ptree& tree);
	virtual void WriteToXML(const boost::property_tree::ptree& tree);
private:
	
	vector<shared_ptr<IPostEffect>> m_pPfxLists;
};
}

#endif PFX_RENDERER_H
