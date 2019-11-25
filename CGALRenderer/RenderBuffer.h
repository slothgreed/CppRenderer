#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

namespace KI
{
class RenderBuffer : public GLObject
{
public:
	RenderBuffer();
	~RenderBuffer();

	virtual void Bind();
	virtual void Generate();
	virtual void UnBind();
	virtual void Dispose();

private:
};
}

#endif // !RENDERBUFFER_H
