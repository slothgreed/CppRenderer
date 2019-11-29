#ifndef RENDER_TEXTURE
#define	RENDER_TEXTURE

namespace KI
{
class RenderTexture : Texture
{
public:
	RenderTexture();
	~RenderTexture();
	void Resize(int width, int height);

private:

};
}

#endif // !RENDER_TEXTURE
