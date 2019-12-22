#ifndef DEFAULT_MATERIAL_H
#define DEFAULT_MATERIAL_H

namespace KI
{
class DefaultMaterial : public IMaterial
{
public:
	DefaultMaterial();
	~DefaultMaterial();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE_DEFAULT; }
	virtual void Bind();
	virtual void UnBind();
	virtual void CompileShader();
	virtual bool Compare(const IMaterial& material);

	void AddTexture(shared_ptr<Texture> texture);
private:
	shared_ptr<DefaultUniform> m_pUniform;
};
}

#endif DEFAULT_MATERIAL_H
