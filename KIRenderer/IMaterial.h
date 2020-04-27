#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
namespace Renderer
{
class RenderData;
class DLL_EXPORT IMaterial
{
public:
	IMaterial();
	virtual ~IMaterial() {};

	virtual const MATERIAL_TYPE Type() const = 0;
	virtual void Bind(shared_ptr<IShader> pShader) = 0;
	virtual void UnBind(shared_ptr<IShader> pShader) = 0;

	virtual void CompileShader(IVertexBuffer* pVertexBuffer) = 0;
	virtual bool Compare(const IMaterial& material) = 0;

	shared_ptr<IShader> GetShader() { return m_pShader; };
	bool NeedReCompileShader() { return m_bReCompileShader; }
protected:
	void SetShader(shared_ptr<IShader> pShader) { m_pShader = pShader; m_bReCompileShader = false; };
	bool m_bReCompileShader;
private:
	shared_ptr<IShader> m_pShader;
};
}
}
#endif IMATERIAL_H
