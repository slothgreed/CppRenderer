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
protected:
	string m_name;

private:

	struct UI
	{
		UI() {}
		CheckBoxUI meshVisibility;
		ColorPicker4UI meshColor;

		CheckBoxUI edgeVisibility;
		ColorPicker4UI edgeColor;

		CheckBoxUI bdbVisibility;
		ColorPicker4UI bdbColor;
		
		CheckBoxUI normalVisibility;
		ColorPicker4UI normalColor;
	};

	UI m_ui;
	BDB m_bdb;
	void SetRenderData();
};
}
}

#endif MODEL_NODE_H
