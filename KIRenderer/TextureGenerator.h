#ifndef TEXTURE_GENERATOR_H
#define TEXTURE_GENERATOR_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT TextureGenerator
{
public:
	TextureGenerator();
	~TextureGenerator();

	static void UVTexture(int size, TextureData& data);
	static void RandomTexture(int size, int alpha, TextureData& data);
	static void FillTexture(vec4 color, TextureData& data);
	static void Load(const string& filePath, TextureData& data);
private:

};
}
}

#endif TEXTURE_GENERATOR_H