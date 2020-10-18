#ifndef RENDER_TEXTURE
#define	RENDER_TEXTURE

namespace KI
{
namespace Gfx
{
class DLL_EXPORT RenderTexture : public Texture
{
public:
	RenderTexture();
	~RenderTexture();

	void SetAttachment(GLenum attachment) { m_attachment = attachment; }
	GLenum Attachment() { return m_attachment; }
	bool GetPixels(ReadPixelArgs& args);

	static TextureData DefaultColorTextureData(int width, int height);
	static TextureData DefaultDepthTextureData(int width, int height);
private:
	GLenum m_attachment;
};
}
}

#endif // !RENDER_TEXTURE
