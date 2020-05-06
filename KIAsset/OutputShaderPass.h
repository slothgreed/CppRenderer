#ifndef OUTPUT_MATERIAL_H
#define OUTPUT_MATERIAL_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT OutputShaderPass : public IShaderPass
{
	enum UNIFORM_LOCATION : unsigned short
	{
		UNIFORM_LOCATION_COLOR_TEXTURE,
		UNIFORM_LOCATION_NUM
	};
public:
	OutputShaderPass();
	~OutputShaderPass();

	virtual const MATERIAL_TYPE Type() const { return MATERIAL_TYPE::MATERIAL_TYPE_OUTPUT_BUFFER; };
	virtual void CompileShader(IVertexBuffer* pVertexBuffer) override;
	virtual bool Compare(const IShaderPass& material);
	void AddColorTexture(shared_ptr<Texture> colorTexture);

};
}
}

#endif OUTPUT_MATERIAL_H