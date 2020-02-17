#ifndef MANIPULATOR_NODE_H
#define MANIPULATOR_NODE_H

namespace KI
{
class ManipulatorNode : public IModelNode
{
public:
	ManipulatorNode();
	~ManipulatorNode();

	virtual void ShowProperty();
	virtual void Draw();
private:
	void GenManipulatorHandleVBO(DefaultVertexBuffer* pFaceBuffer, DefaultVertexBuffer* pEdgeBuffer, MANIPULATOR_HANDLE handle);
	void SetRenderData();
	MoveManipulator manipulator;
	map<MANIPULATOR_HANDLE, DefaultVertexBuffer*> m_pFaceBuffers;
	map<MANIPULATOR_HANDLE, DefaultVertexBuffer*> m_pEdgeBuffers;
	DefaultMaterial* m_pMaterial;
};
}


#endif MANIPULATOR_NODE_H