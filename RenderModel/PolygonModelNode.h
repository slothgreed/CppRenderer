#ifndef MODEL_NODE_H
#define MODEL_NODE_H
namespace KI
{
namespace RenderModel
{
class DLL_EXPORT PolygonModelNode : public IRenderModelNode
{
public:
	PolygonModelNode(shared_ptr<IModel> model);
	~PolygonModelNode();
	virtual void ShowProperty() override;
	virtual void ShowUI() override;
	virtual void Update(void* sender, IEventArgs* args) override;
	IPolygonModel* GetModel();

	void VisibleBDB(bool visibility);
	void VisibleNormal(bool visibility);
	void VisibleFace(bool visibility);
	void VisibleEdge(bool visibility);
	shared_ptr<IVertexBuffer> GetVertexBuffer();
protected:
	string m_name;

private:

	struct UI
	{
		UI() : visibleBDB(false), visibleNormal(false) {}
		bool visibleBDB;
		bool visibleNormal;
	};

	UI m_ui;
	BDB m_bdb;
	void SetRenderData();
};
}
}

#endif MODEL_NODE_H
