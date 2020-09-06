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
	Begin();
	if (Width() == 0 ||
		Height() == 0 ||
		Width() < args.width ||
		Height() < args.height)
	{
		assert(0);
		return false;
	}

	if (args.format == 0) {
		args.format = Format();
	}

	if (args.type == 0) {
		args.type = ColorComponentType();
	}

	if (args.format != Format() ||
		args.type != ColorComponentType()) {
		assert(0);
		return false;
	}

	int dataSize = glEx::ColorFormatSize(args.format);
	args.pixels.NewArray(m_data.type, dataSize, args.width * args.height);

	Logger::GLError();

	glReadPixels(
		args.x,
		args.y,
		args.width,
		args.height,
		args.format,
		args.type,
		args.pixels.Data());

	Logger::GLError();

	End();
	return true;
}
}
}
