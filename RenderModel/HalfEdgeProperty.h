#ifndef HALF_EDGE_PROPERTY_H
#define HALF_EDGE_PROEPRTY_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT HalfEdgeProperty : public IRenderModelProperty
{
public:
	HalfEdgeProperty();
	~HalfEdgeProperty() {};

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_HALFEDGE; }
	virtual void Draw(shared_ptr<UniformStruct> pUniform) override;
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
private:
	void GetVBOData(HalfEdgeDS* model, vector<vec3>& position, vector<vec3>& color, bool needColor);

	shared_ptr<IShader> m_pShader;
	shared_ptr<RenderData> m_pRenderData;
};
}
}

#endif // !HALF_EDGE_PROEPRTY_H

