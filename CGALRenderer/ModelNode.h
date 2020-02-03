#ifndef MODEL_NODE_H
#define MODEL_NODE_H
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
	virtual void Draw() override;
	virtual void ShowProperty() override;
	virtual void Update(void* sender, shared_ptr<EventArgs> args) override;

	void VisibleBDB(bool visibility);
	void VisibleNormal(bool visibility);
protected:
	string m_name;
	shared_ptr<IMaterial> m_pFaceMaterial;
	shared_ptr<IMaterial> m_pEdgeMaterial;

private:
	BDB m_bdb;
	void SetRenderData();
};

}

#endif MODEL_NODE_H
