namespace KI
{
namespace Gfx
{
RenderTexture::RenderTexture()
{
}

RenderTexture::~RenderTexture()
{
}


void RenderTexture::Resize(int width, int height)
{
	TextureData textureData = m_data;
	textureData.width = width;
	textureData.height = height;
	textureData.pixels = 0;
	Begin();
	Set(textureData);
	End();
}
}
}
