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
	virtual void Draw() override;
	virtual void Build(IModel* model) override;
	virtual void Update(IModel* model) override;
private:
	void GetVBOData(HalfEdgeDS* model, vector<vec3>& position, vector<vec3>& color, bool needColor);

	shared_ptr<IShader> m_pShader;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
};

}

#endif // !HALF_EDGE_PROEPRTY_H

