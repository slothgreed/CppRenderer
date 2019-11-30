#ifndef DEFAULT_MATERIAL_H
#define DEFAULT_MATERIAL_H

namespace KI
{
class DefaultMaterial : public IMaterial
{
public:
	DefaultMaterial();
	~DefaultMaterial();

	virtual void Bind() {};
	virtual void UnBind() {};
	virtual void CompileShader();
	virtual void Draw();
	void AddTexture(shared_ptr<Texture> texture);
private:
	shared_ptr<Texture> m_pTexture;
};
}

#endif DEFAULT_MATERIAL_H
