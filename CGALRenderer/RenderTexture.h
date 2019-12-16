#ifndef RENDER_TEXTURE
#define	RENDER_TEXTURE

namespace KI
{
class RenderTexture : public Texture
{
public:
	RenderTexture();
	~RenderTexture();
	void Resize(int width, int height);
	void SetAttachment(GLenum attachment) { m_attachment = attachment; }
	GLenum Attachment() { return m_attachment; }
private:
	GLenum m_attachment;
};
}

#endif // !RENDER_TEXTURE
