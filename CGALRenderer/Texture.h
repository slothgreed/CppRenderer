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
		width(1),
		height(1),
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

	virtual void Bind();
	virtual void Generate();
	virtual void UnBind();
	virtual void Dispose();
	
	void Active(GLint i);
	void Set(const TextureData& data);
private:

};
}

#endif	// ! TEXTURE_H
