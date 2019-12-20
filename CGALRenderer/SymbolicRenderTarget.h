#ifndef SYMBOLIC_RENDERTARGET_H
#define	SYMBOLIC_RENDERTARGET_H

namespace KI
{
// GL_BACK, GL_FRONT �Ȃǂ�FBO���g��Ȃ��W���̃o�b�t�@�p
class SymbolicRenderTarget : public IRenderTarget
{
public:
	SymbolicRenderTarget(GLenum drawBuffer);
	~SymbolicRenderTarget();

	virtual void Resize(int width, int height);
	virtual void Dispose();
protected:
	virtual void Bind();
	virtual void UnBind();

private:
	GLenum m_drawBuffer;

};

}



#endif // !SYMBOLIC_RENDERTARGET_H