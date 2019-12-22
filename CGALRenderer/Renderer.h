#ifndef RENDERER_H
#define RENDERER_H

namespace KI
{

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Draw(shared_ptr<Camera> pCamera);
private:
	
	vector<shared_ptr<IPostEffect>> m_pPfxLists;
};
}

#endif RENDERER_H