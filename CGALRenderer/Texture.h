#ifndef TEXTUREBUFFER_H
#define TEXTUREBUFFER_H

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

#endif
