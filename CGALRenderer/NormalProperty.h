#ifndef NORMAL_PROPERTY_H
#define NORMAL_PROPERTY_H

namespace KI
{

// 法線プロパティ
class NormalProperty : public IModelProperty
{
public:
	NormalProperty();
	~NormalProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_VECTOR; }
	virtual void Draw();
	virtual void Update(IModelNode* pModelNode);
private:
	void Build(IModelNode* pModelNode);
	void SetVBOData(IModelNode* pModelNode);
	shared_ptr<NormalVisualizeShading> m_pShading;
	shared_ptr<RenderData> m_pRenderData;
};

}


#endif // !VECTOR_PROPERTY_H

