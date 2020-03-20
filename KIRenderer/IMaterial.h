#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT IMaterial
{
public:
	IMaterial() {};
	virtual ~IMaterial() {};

	virtual const MATERIAL_TYPE Type() const = 0;
	virtual void Bind() = 0;
	virtual void UnBind() = 0;

	virtual shared_ptr<IShader> CompileShader(IVertexBuffer* pVertexBuffer) = 0;
	virtual bool Compare(const IMaterial& material) = 0;
	void Draw(IVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer = nullptr);

protected:
	shared_ptr<IShader> m_pShader;
};
}
}
#endif IMATERIAL_H
