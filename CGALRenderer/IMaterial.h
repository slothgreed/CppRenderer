#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
class IMaterial
{
public:
	IMaterial() {};
	virtual ~IMaterial() {};

	virtual const MATERIAL_TYPE Type() const = 0;
	virtual void SetVertexBuffer(shared_ptr<IVertexBuffer> vertexBuffer);
	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	virtual void CompileShader() = 0;
	virtual bool Compare(const IMaterial& material) = 0;
	virtual void Draw();
	void Draw(IVertexBuffer* pVertexBuffer);

protected:
	shared_ptr<IVertexBuffer> m_pVertexBuffer;
	shared_ptr<IShader> m_pShader;
};
}

#endif IMATERIAL_H
