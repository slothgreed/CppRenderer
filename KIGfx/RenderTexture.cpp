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

const TextureData& RenderTexture::DefaultColorTextureData(int width, int height)
{
	TextureData data;
	data.target = GL_TEXTURE_2D;
	data.level = 0;
	data.internalformat = GL_RGBA;
	data.width = width;
	data.height = height;
	data.border = 0;
	data.format = GL_RGBA;
	data.type = GL_UNSIGNED_BYTE;
	data.pixels = 0;
	return data;
}
const TextureData& RenderTexture::DefaultDepthTextureData(int width, int height)
{
	TextureData data;
	data.target = GL_TEXTURE_2D;
	data.level = 0;
	data.internalformat = GL_DEPTH_COMPONENT;
	data.width = width;
	data.height = height;
	data.border = 0;
	data.format = GL_DEPTH_COMPONENT;
	data.type = GL_UNSIGNED_BYTE;
	data.pixels = 0;

	return data;
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
