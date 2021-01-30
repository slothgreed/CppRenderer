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

	void VisibleNormal(bool visibility);
	shared_ptr<IVertexBuffer> GetVertexBuffer();
protected:
	string m_name;

private:
	enum RENDER_DATA
	{
		MESH = 0,
		Edge = 1,
	};

	struct UI
	{
		UI() : visibleBDB(false), visibleNormal(false) {}
		bool visibleBDB;
		bool visibleNormal;
		bool visibleMesh;
		bool visibleEdge;
	};

	UI m_ui;
	BDB m_bdb;
	void SetRenderData();
};
}
}

#endif MODEL_NODE_H
