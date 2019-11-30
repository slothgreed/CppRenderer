#ifndef IVERTEX_BUFFER_H
#define IVERTEX_BUFFER_H
namespace KI
{
class IVertexBuffer
{
public:
	IVertexBuffer() {};
	~IVertexBuffer() {};

	virtual string Type() = 0;
	virtual void Draw() = 0;	// need call glDrawArrays or glDrawElements
private:

};
}
#endif IVERTEX_BUFFER_H
