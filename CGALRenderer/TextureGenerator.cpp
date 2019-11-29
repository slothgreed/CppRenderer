namespace KI
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

	texture.format = GL_TEXTURE_2D;
	GLuint* pixel = new GLuint[size * size * 4];
	texture.pixels = pixel;
	int halfSize = size / 2;
	int width = 0;
	int height = 0;
	for (int i = 0; i < size; i++)
	{
		width = i * 4 * size;
		for (int j = 0; j < size; j++)
		{
			height = j * 4;

			if (halfSize < width && halfSize < height ||
				halfSize > width && halfSize > height
				)
			{
				pixel[width + height + 0] = 1;
				pixel[width + height + 1] = 1;
				pixel[width + height + 2] = 1;
				pixel[width + height + 3] = 1;
			}
			else
			{
				pixel[width + height + 0] = 0;
				pixel[width + height + 1] = 0;
				pixel[width + height + 2] = 0;
				pixel[width + height + 3] = 1;
			}
		}
	}
}

}
