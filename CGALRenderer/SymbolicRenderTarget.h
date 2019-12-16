#ifndef SYMBOLIC_RENDERTARGET_H
#define	SYMBOLIC_RENDERTARGET_H

namespace KI
{
// GL_BACK, GL_FRONT などのFBOを使わない標準のバッファ用
class SymbolicRenderTarget : public IRenderTarget
{
public:
	SymbolicRenderTarget(GLenum drawBuffer);
	~SymbolicRenderTarget();

	virtual void Bind();
	virtual void UnBind();
	virtual void Resize(int width, int height);
	virtual void Dispose();
private:
	GLenum m_drawBuffer;

};

}



#endif // !SYMBOLIC_RENDERTARGET_H
