#ifndef TEXTURE_H
#define TEXTURE_H

namespace KI
{

class TextureData
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
			delete pixels;
			pixels = 0;
		}
	}
};

class Texture : public GLObject
{
public:
	Texture();
	~Texture();

	virtual void Generate() override;
	virtual void Dispose() override;

	int Width() { return m_data.width; };
	int Height() { return m_data.height; };

	void Set(const TextureData& data);
protected:

	virtual void Bind();
	virtual void UnBind();
	TextureData m_data;	// pixelèÓïÒÇÕèdÇ≠Ç»ÇÈÇÃÇ≈éùÇΩÇ»Ç¢ÅB

private:
	void SetTextureData(const TextureData& data);
};
}

#endif	// ! TEXTURE_H
