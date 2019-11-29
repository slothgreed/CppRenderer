#ifndef IVERTEX_BUFFER_H
#define IVERTEX_BUFFER_H
namespace KI
{
class IVertexBuffer
{
public:
	IVertexBuffer() {};
	~IVertexBuffer() {};

	virtual void Draw() = 0;
private:

};
}
#endif IVERTEX_BUFFER_H
