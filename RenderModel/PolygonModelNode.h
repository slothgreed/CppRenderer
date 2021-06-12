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
	virtual void InitializeUI();
	virtual void ShowUI() override;
	virtual void Update(void* sender, IEventArgs* args) override;
	IPolygonModel* GetModel();

	void VisibleNormal(bool visibility);
	shared_ptr<VertexBuffer> GetVertexBuffer();
	shared_ptr<ArrayBuffer> GetPositionBuffer();
	shared_ptr<ArrayBuffer> GetNormalBuffer();
	shared_ptr<ArrayBuffer> GetColorBuffer();
	shared_ptr<ArrayBuffer> GetTexcoordBuffer();
	shared_ptr<IndexBuffer> GetIndexBuffer();

protected:
	string m_name;

private:

	struct UI
	{
		UI() : visibleMesh(true),visibleEdge(false),visibleBDB(false),visibleNormal(false) {}
		CheckBoxUI visibleMesh;
		ColorPicker4UI meshColor;

		CheckBoxUI visibleEdge;
		ColorPicker4UI edgeColor;

		CheckBoxUI visibleBDB;
		ColorPicker4UI bdbColor;
		
		CheckBoxUI visibleNormal;
		ColorPicker4UI normalColor;
	};

	UI m_ui;
	BDB m_bdb;
	void SetRenderData();
};
}
}

#endif MODEL_NODE_H
