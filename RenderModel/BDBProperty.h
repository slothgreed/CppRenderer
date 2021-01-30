#ifndef BDB_PROPERTY_H
#define BDB_PROEPRTY_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT BDBProperty : public IRenderModelProperty
{
public:
	BDBProperty();
	~BDBProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_BDB; }
	virtual void Build(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
private:
	void GetBDBPosition(const BDB& bdb, vector<vec3>& position);
	shared_ptr<RenderData> m_pRenderData;
};
}
}

#endif // !BDB_PROPERTY_H
