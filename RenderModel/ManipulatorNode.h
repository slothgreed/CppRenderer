#ifndef MANIPULATOR_NODE_H
#define MANIPULATOR_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT ManipulatorNode : public IModelNode
{
public:
	ManipulatorNode(MANIPULATOR_TYPE type);
	~ManipulatorNode();

	virtual void ShowProperty() override;
private:
	virtual void DrawCore(shared_ptr<UniformStruct> pUniform) override;
	void GenManipulatorHandleVBO(
		RenderData* pFaceData,
		MANIPULATOR_HANDLE handle);
	void SetRenderData();
	map<MANIPULATOR_HANDLE, shared_ptr<RenderData>> m_pFaceDatas;
	MANIPULATOR_TYPE m_ManipulatorType;
	shared_ptr<IManipulatorModel> m_pManipulator;
	shared_ptr<BasicShading> m_pShading;
};
}
}

#endif MANIPULATOR_NODE_H