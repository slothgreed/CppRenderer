#ifndef HALF_EDGE_PROPERTY_H
#define HALF_EDGE_PROEPRTY_H

namespace KI
{
class HalfEdgeProperty : public IModelProperty
{
public:
	HalfEdgeProperty();
	~HalfEdgeProperty() {};

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_HALFEDGE; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void Build(IModelNode* model) override;
	virtual void Update(IModelNode* model) override;
private:
	void GetVBOData(HalfEdgeDS* model, vector<vec3>& position, vector<vec3>& color, bool needColor);

	shared_ptr<IShader> m_pShader;
	shared_ptr<RenderData> m_pRenderData;
};

}

#endif // !HALF_EDGE_PROEPRTY_H

