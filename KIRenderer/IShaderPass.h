#ifndef ISHADERPASS_H
#define ISHADERPASS_H

namespace KI
{
namespace Renderer
{
class RenderData;
class DLL_EXPORT IShaderPass
{
public:
	IShaderPass();
	virtual ~IShaderPass() {};

	virtual const MATERIAL_TYPE Type() const = 0;
	virtual void Bind();
	virtual void UnBind();

	virtual void CompileShader(IVertexBuffer* pVertexBuffer) = 0;
	virtual bool Compare(const IShaderPass& material) = 0;

	shared_ptr<IShader> GetShader() { return m_pShader; };

	shared_ptr<UniformSet> GetUniform() { return m_pUniform; }
	bool NeedReCompileShader() { return m_bReCompileShader; }
protected:
	void SetShader(shared_ptr<IShader> pShader);
	bool m_bReCompileShader;
private:
	shared_ptr<IShader> m_pShader;
	shared_ptr<UniformSet> m_pUniform;
};
}
}
#endif ISHADERPASS_H
