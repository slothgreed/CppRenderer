#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
class IMaterial
{
public:
	IMaterial() {};
	~IMaterial() {};

	virtual void SetVertexBuffer(shared_ptr<IVertexBuffer> vertexBuffer);

	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	virtual void CompileShader() = 0;
	virtual void Draw() = 0;
protected:
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IShader> m_pShader;
};
}

#endif IMATERIAL_H
