#ifndef RENDERTARGET_H
#define	RENDERTARGET_H

namespace KI
{

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	void Resize(int width, int height);
private:
	shared_ptr<FrameBuffer> m_pFrameBuffer;
	vector<shared_ptr<RenderTexture>> m_pOutputBuffer;
	shared_ptr<RenderTexture> m_pDepthBuffer;
};

}

#endif // !RENDERTARGET_H

