#ifndef EDGE_PROPERTY_H
#define EDGE_PROEPRTY_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT EdgeProperty : public IRenderModelProperty
{
public:
	EdgeProperty();
	~EdgeProperty() {};

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_EDGE; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
private:

	shared_ptr<IShader> m_pShader;
	shared_ptr<RenderData> m_pRenderData;
};
}
}

#endif // !HALF_EDGE_PROEPRTY_H

