#ifndef RENDERTARGET_H
#define	RENDERTARGET_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT RenderTarget : public IRenderTarget
{
public:
	RenderTarget();
	~RenderTarget();
	void Initialize(int outputBufferNum, int width, int height);
	virtual void Resize(int width, int height);
	virtual void Dispose();
	shared_ptr<RenderTexture> ColorTexture(int index);
	void CopyColorBuffer(int index, Texture* texture);
	void CopyDepthBuffer(Texture* texture);

protected:
	virtual void Bind();
	virtual void UnBind();

private:
	shared_ptr<FrameBuffer> m_pFrameBuffer;
	vector<shared_ptr<RenderTexture>> m_pOutputBuffer;
	shared_ptr<RenderTexture> m_pDepthBuffer;
};
}
}

#endif // !RENDERTARGET_H

