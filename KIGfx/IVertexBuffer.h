#ifndef IVERTEX_BUFFER_H
#define IVERTEX_BUFFER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IVertexBuffer
{
public:
	IVertexBuffer() {};
	~IVertexBuffer() {};

	virtual SHADER_TYPE Type() = 0;
	virtual void Draw() = 0;	// need call glDrawArrays or glDrawElements
private:

};
}
}
#endif IVERTEX_BUFFER_H
