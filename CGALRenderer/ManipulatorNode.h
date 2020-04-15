#ifndef MANIPULATOR_NODE_H
#define MANIPULATOR_NODE_H

namespace KI
{
class ManipulatorNode : public IModelNode
{
public:
	ManipulatorNode();
	~ManipulatorNode();

	virtual void ShowProperty() override;
	virtual void Draw() override;
private:
	void GenManipulatorHandleVBO(
		RenderData* pFaceData,
		RenderData* pEdgeData,
		MANIPULATOR_HANDLE handle);
	void SetRenderData();
	MoveManipulator manipulator;
	map<MANIPULATOR_HANDLE, shared_ptr<RenderData>> m_pFaceDatas;
	map<MANIPULATOR_HANDLE, shared_ptr<RenderData>> m_pEdgeDatas;
	shared_ptr<DefaultMaterial> m_pMaterial;
};
}


#endif MANIPULATOR_NODE_H