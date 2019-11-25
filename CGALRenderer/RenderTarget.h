#ifndef RENDERTARGET_H
#define	RENDERTARGET_H

namespace KI
{

class RenderTarget
{
public:
	RenderTarget();
	~RenderTarget();

private:
	shared_ptr<FrameBuffer> m_pFrameBuffer;
	shared_ptr<RenderBuffer> m_pOutputBuffer;

};

}

#endif // !RENDERTARGET_H

