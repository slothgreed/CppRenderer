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
		m_Instance->Initialize();
	}

	return *m_Instance;
}

void TextTextureGenerator::Charactor::BufferCopy(unsigned char * buf)
{
	RELEASE_INSTANCE(m_buffer);
	int size = int(m_size.x * m_size.y * sizeof(unsigned char));
	m_buffer = new unsigned char[size];
	std::memcpy(m_buffer, buf, size);
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

	//string texts = "abcdefghijklmnopqrstuvwxvzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	//string texts = "0123456789";
	string texts = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

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
			vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			vec2(face->glyph->advance.x / 64, face->glyph->bitmap.rows));
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
	m_texture = make_shared<Texture>();
	m_texture->Generate();
	m_texture->PixelStore(1);

	float width = 0;
	float height = 0;
	for (auto itr = m_charactos.begin(); itr != m_charactos.end(); itr++) 
	{
		width += itr->second->m_size.x;
		height = std::max(height, itr->second->m_size.y);
	}

	assert(width != 16392);	// TODO: •K—v‚É‚È‚Á‚½‚çŽÀ‘•
	int pixelSize = int(width * height);
	unsigned char* pixel = new unsigned char[pixelSize];
	int counter = 0;
	for (int i = 0; i < height; i++) {
		for (auto itr = m_charactos.begin(); itr != m_charactos.end(); itr++)
		{
			for (int j = 0; j < itr->second->m_size.x; j++)
			{
				int index = i * (int)itr->second->m_size.x + j;

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
	data.width = (GLsizei)width;
	data.height = (GLsizei)height;
	data.format = GL_RED;
	data.type = GL_UNSIGNED_BYTE;
	data.pixels = pixel;
	m_texture->Begin();
	m_texture->Set(data);
	m_texture->End();
}

void TextTextureGenerator::Generate(const std::string& text, std::vector<vec3>* position, std::vector<int>* index, std::vector<vec2>* texcoord)
{
	if (m_Initialize == false) {
		return;
	}
	float originPos = 0;
	float viewSize = 1;
	position->resize(text.size() * 6);
	texcoord->resize(text.size() * 6);
	index->resize(text.size() * 6);
	for (int i = 0; i < text.size(); i++)
	{
		auto charactor = m_charactos[text[i]];
		int index0 = 6 * i;
		int index1 = 6 * i + 1;
		int index2 = 6 * i + 2;
		int index3 = 6 * i + 3;
		int index4 = 6 * i + 4;
		int index5 = 6 * i + 5;

		(*position)[index0] = (vec3(originPos, 0.0, 0.0));
		(*position)[index1] = (vec3(originPos, viewSize, 0.0));
		(*position)[index2] = (vec3(originPos + viewSize, 0.0, 0.0));
		(*position)[index3] = (vec3(originPos + viewSize, 0.0, 0.0));
		(*position)[index4] = (vec3(originPos, viewSize, 0.0));
		(*position)[index5] = (vec3(originPos + viewSize, viewSize, 0.0));

		originPos += viewSize;

		(*texcoord)[index0] = (charactor->m_position);
		(*texcoord)[index1] = (vec2(charactor->m_position.x, charactor->m_position.y + charactor->m_size.y));
		(*texcoord)[index2] = (vec2(charactor->m_position.x + charactor->m_size.x, charactor->m_position.y));
		(*texcoord)[index3] = (vec2(charactor->m_position.x + charactor->m_size.x, charactor->m_position.y));
		(*texcoord)[index4] = (vec2(charactor->m_position.x, charactor->m_position.y + charactor->m_size.y));
		(*texcoord)[index5] = (charactor->m_position + charactor->m_size);

		(*index)[index0] = index0;
		(*index)[index1] = index1;
		(*index)[index2] = index2;
		(*index)[index3] = index3;
		(*index)[index4] = index4;
		(*index)[index5] = index5;
	}
}

}
}
