#ifndef QUAD_POSITION_PROPERTY_H
#define QUAD_POSITION_PROEPRTY_H

namespace KI
{
namespace RenderModel
{

class QuadPositionPropertyArgs : public IRenderModelPropertyArgs
{
public:
	QuadPositionPropertyArgs(int level) :m_level(level) {};
	~QuadPositionPropertyArgs() {};
	int Level() { return m_level; }
	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_QUAD_POSITION; }
private:
	int m_level;
};

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
		SliderIntUI pointSize;
		SliderIntUI level;
	};

	shared_ptr<HalfEdgeModel> GetHalfEdgeModel();
	UI m_ui;
	void SetVBOData(IModelNode* pModelNode, QuadPositionPropertyArgs* pPropertyArgs);
	float m_pointSize;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
	shared_ptr<ArrayBuffer> m_pTangentBuffer;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<BasicShading> m_pShading;
};

}
}

#endif // !QUAD_POSITION_PROEPRTY_H
