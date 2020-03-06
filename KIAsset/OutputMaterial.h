#ifndef OUTPUT_MATERIAL_H
#define OUTPUT_MATERIAL_H

namespace KI
{
namespace Asset
{
class OutputMaterial : public IMaterial
{
	enum UNIFORM_LOCATION : unsigned short
	{
		UNIFORM_LOCATION_COLOR_TEXTURE,
		UNIFORM_LOCATION_NUM
	};
public:
	OutputMaterial();
	~OutputMaterial();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE::MATERIAL_TYPE_OUTPUT_BUFFER; };
	virtual void Bind();
	virtual void UnBind();
	virtual shared_ptr<IShader> CompileShader(IVertexBuffer* pVertexBuffer) override;
	virtual bool Compare(const IMaterial& material);
	void AddColorTexture(shared_ptr<Texture> colorTexture);

private:
	shared_ptr<OutputUniform> m_pUniform;

};
}
}

#endif OUTPUT_MATERIAL_H