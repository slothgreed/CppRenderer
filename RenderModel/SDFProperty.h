#ifndef SDF_PROPERTY_HPP
#define SDF_PROPERTY_HPP
namespace KI
{
namespace RenderModel
{
class DLL_EXPORT SDFProperty : public IRenderModelProperty
{
public:
	SDFProperty();
	~SDFProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_SDF; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;

private:
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<DefaultVertexBuffer> m_sdfBuffer;
};

}
}
#endif SDF_PROPERTY_HPP
