#ifndef COMPOSIT_SHADERL_H
#define COMPOSIT_SHADERL_H

namespace KI
{
namespace Renderer
{
class CompositUniform;
class DLL_EXPORT CompositShader : public IShader
{
public:

	enum COMPOSIT_UNIFORM : unsigned short
	{
		COMPOSIT_UNIFORM_SOURCE_TEXTURE,
		COMPOSIT_UNIFORM_TARGET_TEXTURE,
		COMPOSIT_UNIFORM_NUM
	};

	CompositShader();
	~CompositShader();
	virtual SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_COMPOSIT; }

	virtual void Initialize() override;
	virtual void FetchUniformLocation() override;
	virtual void Bind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform) override;
	virtual void UnBind(shared_ptr<IMaterial> pMaterial, shared_ptr<UniformSet> pUniform) override;

};

class DLL_EXPORT CompositUniform : public IUniform
{
	SHADER_TYPE Type() { return SHADER_TYPE::SHADER_TYPE_COMPOSIT; }
	shared_ptr<Texture> m_pSource;
	shared_ptr<Texture> m_pDestination;
};

}
}
#endif COMPOSIT_SHADERL_H
