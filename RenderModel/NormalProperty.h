#ifndef NORMAL_PROPERTY_H
#define NORMAL_PROPERTY_H

namespace KI
{
namespace RenderModel
{
// 法線プロパティ
class DLL_EXPORT NormalProperty : public IRenderModelProperty
{
public:
	NormalProperty();
	~NormalProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_NORMAL; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;

private:
	void SetVBOData(IModelNode* pModelNode);
	shared_ptr<NormalVisualizeShading> m_pShading;
	shared_ptr<RenderData> m_pRenderData;
};
}
}


#endif // !VECTOR_PROPERTY_H

