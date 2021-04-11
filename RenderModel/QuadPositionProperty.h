#ifndef QUAD_POSITION_PROPERTY_H
#define QUAD_POSITION_PROEPRTY_H

namespace KI
{
namespace RenderModel
{

class QuadPositionProperty : public IRenderModelProperty
{
public:
	QuadPositionProperty();
	~QuadPositionProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_QUAD_POSITION; }
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
	virtual void InitializeUI();
	virtual void ShowUI();

private:

	struct UI
	{
		SliderFloatUI tangent;
		SliderFloatUI offset;
		ColorPicker4UI color;
	};

	UI m_ui;
	void SetVBOData(IModelNode* pModelNode);
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
	shared_ptr<ArrayBuffer> m_pTangentBuffer;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<BasicShading> m_pShading;
};

}
}

#endif // !QUAD_POSITION_PROEPRTY_H
