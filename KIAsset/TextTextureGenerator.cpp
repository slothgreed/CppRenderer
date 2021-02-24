namespace KI
{
namespace Asset
{
#include "ft2build.h"
#include FT_FREETYPE_H

TextTextureGenerator*	TextTextureGenerator::m_Instance = nullptr;
TextTextureGenerator& TextTextureGenerator::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new TextTextureGenerator();
	}

	return *m_Instance;
}

void TextTextureGenerator::Charactor::BufferCopy(unsigned char * buf)
{
	RELEASE_INSTANCE(m_buffer);
	m_buffer = new unsigned char[m_pixelSize.x * m_pixelSize.y];
	std::memcpy(m_buffer, buf, m_pixelSize.x * m_pixelSize.y * sizeof(unsigned char));
}

bool TextTextureGenerator::Initialize()
{
	std::string filePath = "C:\\Users\\stmnd\\Desktop\\Fonts\\arial.ttf";
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return false;
	}

	FT_Face face;
	if (FT_New_Face(ft, filePath.data(), 0, &face))
	{
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return false;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
		return false;
	}

	FT_Set_Pixel_Sizes(face, 0, 48);
	

	//string texts = "abcdefghijklmnopqrstuvwxvzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	string texts = "0123456789";


	vec2 posOffset = vec2(0);
	for (int i = 0; i < texts.size(); i++)
	{
		// load character glyph 
		if (FT_Load_Char(face, texts[i], FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}


		auto charctor = new Charactor(
			vec2(posOffset),
			vec2(face->glyph->advance.x / 64, face->glyph->bitmap.rows),
			vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows));
			//vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			//face->glyph->bitmap.buffer);

		charctor->BufferCopy(face->glyph->bitmap.buffer);
		m_charactos[texts[i]] = charctor;


		posOffset.x += charctor->m_size.x;
	}

	GenerateTexture();

	m_Initialize = true;
	return true;

}

void TextTextureGenerator::GenerateTexture()
{
	m_texture = make_unique<Texture>();
	m_texture->Generate();

	float width = 0;
	float height = 0;
	for (auto itr = m_charactos.begin(); itr != m_charactos.end(); itr++) 
	{
		width += itr->second->m_size.x;
		height = std::max(height, itr->second->m_size.y);
	}

	int pixelSize = width * height;
	unsigned int* pixel = new unsigned int[pixelSize];
	int counter = 0;
	for (int i = 0; i < height; i++) {
		for (auto itr = m_charactos.begin(); itr != m_charactos.end(); itr++)
		{
			for (int j = 0; j < itr->second->m_size.x; j++)
			{
				int index = i * height + j;

				if (index < itr->second->m_size.x * itr->second->m_size.y) {
					pixel[counter] = itr->second->m_buffer[index];
				} else {
					pixel[counter] = 0;
				}
				counter++;
			}
		}
	}

	TextureData data;
	data.internalformat = GL_RED;
	data.width = width;
	data.height = height;
	data.format = GL_RED;
	data.type = GL_UNSIGNED_BYTE;
	data.pixels = pixel;
	m_texture->Begin();
	m_texture->Set(data);
	m_texture->End();
}

void TextTextureGenerator::Generate(const std::string& text, std::vector<vec3>* position, std::vector<int>* m_index, std::vector<vec2>* texcoord)
{
	if (Initialize() == false) {
		return;
	}

	float originPos = 0;
	float viewSize = 1;
	for (int i = 0; i < text.size(); i++)
	{
		auto charactor = *m_charactos[text[i]];
		(*position).push_back(vec3(originPos, 0.0, 0.0));
		(*position).push_back(vec3(originPos, viewSize, 0.0));
		(*position).push_back(vec3(originPos + viewSize, 0.0, 0.0));

		(*position).push_back(vec3(originPos + viewSize, 0.0, 0.0));
		(*position).push_back(vec3(originPos, viewSize, 0.0));
		(*position).push_back(vec3(originPos + viewSize, viewSize, 0.0));

		originPos += viewSize;

		(*texcoord).push_back(charactor.m_position);
		(*texcoord).push_back(vec2(charactor.m_position.x, charactor.m_position.y + charactor.m_size.y));
		(*texcoord).push_back(vec2(charactor.m_position.x + charactor.m_size.x, charactor.m_position.y));

		(*texcoord).push_back(vec2(charactor.m_position.x + charactor.m_size.x, charactor.m_position.y));
		(*texcoord).push_back(vec2(charactor.m_position.x, charactor.m_position.y + charactor.m_size.y));
		(*texcoord).push_back(charactor.m_position + charactor.m_size);

		(*m_index).push_back(6 * i);
		(*m_index).push_back(6 * i + 1);
		(*m_index).push_back(6 * i + 2);
		(*m_index).push_back(6 * i + 3);
		(*m_index).push_back(6 * i + 4);
		(*m_index).push_back(6 * i + 5);
	}
}

}
}
