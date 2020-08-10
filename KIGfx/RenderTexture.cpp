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

TextureData RenderTexture::DefaultColorTextureData(int width, int height)
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
TextureData RenderTexture::DefaultDepthTextureData(int width, int height)
{
	TextureData data;
	data.target = GL_TEXTURE_2D;
	data.level = 0;
	data.internalformat = GL_DEPTH_COMPONENT;
	data.width = width;
	data.height = height;
	data.border = 0;
	data.format = GL_DEPTH_COMPONENT;
	data.type = GL_FLOAT;
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

bool RenderTexture::GetPixels(ReadPixelArgs& args)
{
	assert(0);
	//args.width = 640;
	//args.height = 480;
	//if (m_data.width == 0 ||
	//	m_data.height == 0 ||
	//	m_data.width < args.width ||
	//	m_data.height < args.height)
	//{
	//	assert(0);
	//	return false;
	//}

	int dataSize = glEx::ColorFormatSize(args.format);

	args.pixels = new GLubyte[
			(args.width - args.x) *
			(args.height - args.y) *
			dataSize];

	Logger::GLError();

	glReadPixels(
		args.x,
		args.y,
		args.width,
		args.height,
		args.format,
		args.type,
		args.pixels);

	Logger::GLError();

	return true;
}
}
}
