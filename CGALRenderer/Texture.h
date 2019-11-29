#ifndef TEXTURE_H
#define TEXTURE_H

namespace KI
{

class Texture : public GLObject
{
public:
	Texture();
	~Texture();

	virtual void Bind();
	virtual void Generate();
	virtual void UnBind();
	virtual void Dispose();
private:

};
}

#endif	// ! TEXTURE_H
