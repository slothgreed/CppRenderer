#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

namespace KI
{
class FrameBuffer : public GLObject
{
public:
	FrameBuffer();
	~FrameBuffer();

	virtual void Generate();
	virtual void Bind();
	virtual void UnBind();
	virtual void Dispose();

	void Clear();

private:
};

}
#endif // !FRAMEBUFFER_H
