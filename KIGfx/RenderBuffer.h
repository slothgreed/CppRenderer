#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT RenderBuffer : public IGLObject
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
}
#endif // !RENDERBUFFER_H
