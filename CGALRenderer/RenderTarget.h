#ifndef RENDERTARGET_H
#define	RENDERTARGET_H

namespace KI
{

class IRenderTarget
{
public:
	IRenderTarget() {};
	~IRenderTarget() {};

	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	virtual void Resize(int width, int height) = 0;
	virtual void Dispose() = 0;
private:

};

class RenderTarget : public IRenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	void Initialize(int outputBufferNum, int width, int height);
	virtual void Bind();
	virtual void UnBind();
	virtual void Resize(int width, int height);
	virtual void Dispose();
	shared_ptr<RenderTexture> ColorTexture(int index);
	
private:
	shared_ptr<FrameBuffer> m_pFrameBuffer;
	vector<shared_ptr<RenderTexture>> m_pOutputBuffer;
	shared_ptr<RenderTexture> m_pDepthBuffer;
};

}

#endif // !RENDERTARGET_H

