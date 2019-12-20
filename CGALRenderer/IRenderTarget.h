#ifndef IRENDERTARGET_H
#define	IRENDERTARGET_H
namespace KI
{
class IRenderTarget
{
public:
	IRenderTarget() {};
	~IRenderTarget() {};

	void Begin();
	void End();
	virtual void Resize(int width, int height) = 0;
	virtual void Dispose() = 0;
	virtual void Clear();
	void SetClearColor(vec4 color) { m_pClearColor = color; }
protected:
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	bool Modifing() { return m_modifing; }

	vec4 m_pClearColor;

private:
	bool m_modifing;

};
}
#endif // !IRENDERTARGET_H
