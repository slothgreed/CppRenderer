#ifndef MANIPULATOR_NODE_H
#define MANIPULATOR_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT ManipulatorNode : public IRenderModelNode
{
public:
	ManipulatorNode(MANIPULATOR_TYPE type);
	~ManipulatorNode();

	virtual void ClearSelect() override;
	virtual void AddSelect(PICK_TYPE type, shared_ptr<IShading> pShading, int index, int first, int count) override;
	virtual void ShowProperty() override;
protected:
	virtual void PreDraw(shared_ptr<UniformStruct> pUniform, int index) override;
private:
	void GenManipulatorHandleVBO(
		RenderData* pFaceData,
		MANIPULATOR_HANDLE handle);
	void SetRenderData();
	MANIPULATOR_TYPE m_ManipulatorType;
	shared_ptr<IManipulatorModel> m_pManipulator;
	shared_ptr<BasicShading> m_pShading;
	int m_SelectIndex;
};
}
}

#endif MANIPULATOR_NODE_H