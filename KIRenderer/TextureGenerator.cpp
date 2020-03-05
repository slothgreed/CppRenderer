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
}
}
