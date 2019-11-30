#ifndef CGAL_MODEL_NODE_H
#define CGAL_MODEL_NODE_H
namespace KI
{
class IModelNode;
class IShader;
class IVertexBuffer;
class IModelProperty;
class IMaterial;
class ModelNode : public IModelNode
{
public:
	ModelNode(shared_ptr<IModel> model);
	~ModelNode();
	virtual void Draw();
	virtual void ShowProperty();
	virtual void Update(void* sender, shared_ptr<EventArgs> args);

	void SetBDB(BDB bdb);
	void VisibleNormal(bool visibility);
private:
	string m_name;
	shared_ptr<IMaterial> m_pFaceMaterial;
	shared_ptr<IMaterial> m_pEdgeMaterial;

	shared_ptr<IModel> m_pModel;
	vector<shared_ptr<IModelProperty>> m_pProperty;
	BDB m_bdb;
	void SetRenderData();
};

}

#endif CGAL_MODEL_NODE_H
