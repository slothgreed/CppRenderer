#ifndef TEXTURE_H
#define TEXTURE_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT TextureData
{
public:
	GLenum target;
	GLint level;
	GLint internalformat;
	GLsizei width;
	GLsizei height;
	GLint border;
	GLenum format;
	GLenum type;
	const void *pixels;

	TextureData():
		target(GL_TEXTURE_2D),
		level(0),
		internalformat(GL_RGBA),
		width(0),
		height(0),
		border(0),
		format(GL_RGBA),
		type(GL_UNSIGNED_BYTE),
		pixels(0){}

	~TextureData()
	{
		if (pixels != 0)
		{
			delete[] pixels;
			pixels = 0;
		}
	}
};

class DLL_EXPORT Texture : public IGLObject
{
public:
	Texture();
	~Texture();

	virtual void Generate() override;
	virtual void Dispose() override;

	int Width() { return m_data.width; };
	int Height() { return m_data.height; };
	GLuint Format() { return m_data.format; };
	GLuint ColorComponentType() { return m_data.type; };
	void Set(const TextureData& data);
	void Resize(const TextureData& data);
	void Resize(int width, int height);
	void SetSampler(shared_ptr<Sampler> pSampler);
protected:

	virtual void Bind();
	virtual void UnBind();
	TextureData m_data;	// pixelèÓïÒÇÕèdÇ≠Ç»ÇÈÇÃÇ≈éùÇΩÇ»Ç¢ÅB

private:
	void SetTextureData(const TextureData& data);
	shared_ptr<Sampler> m_pSampler;
};
}
}
#endif	// ! TEXTURE_H
