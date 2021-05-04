#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
namespace KI
{
namespace Renderer
{
TextureGenerator::TextureGenerator()
{
}

TextureGenerator::~TextureGenerator()
{
}

void TextureGenerator::UVTexture(int size, TextureData& texture)
{
	texture.target = GL_TEXTURE_2D;
	texture.internalformat = GL_RGBA;
	texture.width = size;
	texture.height = size;
	texture.border = 0;
	texture.format = GL_RGBA;
	texture.type = GL_UNSIGNED_BYTE;
	
	GLubyte* pixel = new GLubyte[size * size * 4];
	texture.pixels = pixel;

	int halfSize = size * 4 / 2;
	int width = 0;
	int height = 0;
	for (int i = 0; i < size; i++)
	{
		width = i * 4 * size;
		for (int j = 0; j < size; j++)
		{
			height = j * 4;

			if (halfSize * size <= width && halfSize <= height ||
				halfSize * size > width && halfSize > height
				)
			{
				pixel[width + height + 0] = 196;
				pixel[width + height + 1] = 196;
				pixel[width + height + 2] = 196;
				pixel[width + height + 3] = 255;
			}
			else
			{
				pixel[width + height + 0] = 0;
				pixel[width + height + 1] = 0;
				pixel[width + height + 2] = 0;
				pixel[width + height + 3] = 255;
			}
		}
	}
}

void TextureGenerator::Load(const string& filePath, TextureData& texture)
{
	if (FileUtility::CheckExtension(filePath, ".png"))
	{
		texture.target = GL_TEXTURE_2D;
		texture.border = 0;
		texture.type = GL_UNSIGNED_BYTE;
		int channel;
		texture.pixels = stbi_load(filePath.c_str(), &texture.width, &texture.height, &channel, 0);
		if (channel == 3)
		{
			texture.internalformat = GL_RGB;
			texture.format = GL_RGB;
		}
		else if (channel == 4)
		{
			texture.internalformat = GL_RGBA;
			texture.format = GL_RGBA;
		}
		else
		{
			assert(0);
		}
	}
	else
	{
		assert(0);
	}
}
void TextureGenerator::RandomTexture(int size, int alpha, TextureData& texture)
{
	texture.target = GL_TEXTURE_2D;
	texture.internalformat = GL_RGBA;
	texture.width = size;
	texture.height = size;
	texture.border = 0;
	texture.format = GL_RGBA;
	texture.type = GL_UNSIGNED_BYTE;

	GLubyte* pixel = new GLubyte[size * size * 4];
	texture.pixels = pixel;
	
	int halfSize = size * 4 / 2;
	int width = 0;
	int height = 0;
	for (int i = 0; i < size; i++)
	{
		width = i * 4 * size;
		for (int j = 0; j < size; j++)
		{
			height = j * 4;
			pixel[width + height + 0] = Gaccho::rnd(0, 255);
			pixel[width + height + 1] = Gaccho::rnd(0, 255);
			pixel[width + height + 2] = Gaccho::rnd(0, 255);
			pixel[width + height + 3] = alpha;
		}
	}
}

void TextureGenerator::FillTexture(const vec4& color, TextureData& texture)
{
	assert(texture.width != 0);
	assert(texture.height != 0);
	assert(texture.pixels == NULL);
	texture.target = GL_TEXTURE_2D;
	texture.internalformat = GL_RGBA;
	texture.format = GL_RGBA;
	texture.border = 0;
	texture.type = GL_UNSIGNED_INT;

	GLubyte* pixel = new GLubyte[texture.width * texture.height * 4];
	texture.pixels = pixel;
	int width = 0;
	int height = 0;
	for (int i = 0; i < texture.width; i++)
	{
		width = i * 4 * texture.height;
		for (int j = 0; j < texture.height; j++)
		{
			height = j * 4;
			pixel[width + height + 0] = (GLubyte)color.x;
			pixel[width + height + 1] = (GLubyte)color.y;
			pixel[width + height + 2] = (GLubyte)color.z;
			pixel[width + height + 3] = (GLubyte)color.w;
		}
	}
}
}
}
