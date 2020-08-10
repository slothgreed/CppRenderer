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
	void Initialize(map<FRAMEBUFFER_ATTACHMENT, shared_ptr<TextureData>>& pRenderTexture);
	void Initialize(int outputBufferNum, int width, int height);
	virtual void Resize(int width, int height);
	virtual void Dispose();
	shared_ptr<RenderTexture> ColorTexture(FRAMEBUFFER_ATTACHMENT index);
	void CopyColorBuffer(FRAMEBUFFER_ATTACHMENT index, Texture* texture);
	void CopyDepthBuffer(Texture* texture);
	shared_ptr<RenderTexture> GetColorTexture(FRAMEBUFFER_ATTACHMENT attachment);
	virtual int ColorTextureNum() override { return (int)m_pOutputBuffer.size(); };
	bool GetPixels(ReadPixelArgs& args, FRAMEBUFFER_ATTACHMENT index);

protected:
	virtual void Bind();
	virtual void UnBind();

private:
	void SetRenderTexture(FRAMEBUFFER_ATTACHMENT attachment, const TextureData& textureData);
	shared_ptr<FrameBuffer> m_pFrameBuffer;
	map<FRAMEBUFFER_ATTACHMENT, shared_ptr<RenderTexture>> m_pOutputBuffer;
	shared_ptr<RenderTexture> m_pDepthBuffer;
};
}
}

#endif // !RENDERTARGET_H

