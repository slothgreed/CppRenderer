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
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void InitializeUI();
	virtual void ShowUI() override;
private:

	struct UI
	{
		SliderFloatUI length;
	};

	UI m_ui;
	void SetVBOData(IModelNode* pModelNode);
	shared_ptr<NormalVisualizeShading> m_pShading;
	shared_ptr<RenderData> m_pRenderData;
};
}
}


#endif // !NORMAL_PROPERTY_H

