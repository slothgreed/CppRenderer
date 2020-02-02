#ifndef HALF_EDGE_PROPERTY_H
#define HALF_EDGE_PROEPRTY_H

namespace KI
{
class DefaultVertexBuffer;
class DefaultShader;
class HalfEdgeProperty : public IModelProperty
{
public:
	HalfEdgeProperty(HalfEdgeDS* model);
	~HalfEdgeProperty() {};

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_HALFEDGE; }
	virtual void Draw() override;
	virtual void Update(void* model);
private:
	void GetVBOData(HalfEdgeDS* model, vector<vec3>& position, vector<vec3>& color, bool needColor);
	void Build(HalfEdgeDS* model);

	shared_ptr<IShader> m_pShader;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
};

}

#endif // !HALF_EDGE_PROEPRTY_H

