#ifndef VERTEX_INDEX_PROPERTY_H
#define VERTEX_INDEX_PROPERTY_H

namespace KI
{
namespace RenderModel
{
class CameraNode;
class DLL_EXPORT VertexIndexPropertyArgs : public IRenderModelPropertyArgs
{
public:

	VertexIndexPropertyArgs(CameraNode* pCameraNode):m_pCameraNode(pCameraNode){};
	~VertexIndexPropertyArgs() {};
	virtual PROPERTY_TYPE PropertyType() { return PROPERTY_TYPE_VERTEX_INDEX; };
	const CameraNode* Camera() const { return m_pCameraNode; }
private:
	CameraNode* m_pCameraNode;
};

// NOTE : By ImGui
class VertexIndexProperty : public IRenderModelProperty
{
public:
	VertexIndexProperty();
	~VertexIndexProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_VERTEX_INDEX; }
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
	virtual void Update(void* sender, IEventArgs* pArgs);
private:
	void SetIndexText(IModelNode* pModelNode, const ICamera* pCamera);
	std::vector<HUDText> m_indexText;
	std::vector<shared_ptr<RenderData>> m_pRenderDatas;
};

}
}

#endif // !VERTEX_INDEX_PROPERTY_H
