#ifndef IRENDERTARGET_H
#define	IRENDERTARGET_H
namespace KI
{
namespace Gfx
{

class DLL_EXPORT IRenderTarget
{
public:
	IRenderTarget();
	~IRenderTarget();

	void Begin();
	void End();
	const vec2& GetSize() { return m_size; };
	virtual void Resize(int width, int height) = 0;
	virtual void Dispose() = 0;
	virtual void Clear(GLbitfield clear = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	virtual bool GetPixels(ReadPixelArgs& args, RENDER_TEXTURE_TYPE type, int index = 0) = 0;
	void SetClearColor(vec4 color) { m_pClearColor = color; }
	virtual int ColorTextureNum() = 0;
protected:
	virtual void Bind() = 0;
	virtual void UnBind() = 0;
	bool GetPixels(ReadPixelArgs& args);
	bool Modifing() { return m_modifing; }
	void SetSize(int width, int height) { m_size.x = (int)width; m_size.y = (int)height; }
	vec4 m_pClearColor;

private:
	bool m_modifing;
	vec2 m_size;

};
}
}
#endif // !IRENDERTARGET_H
