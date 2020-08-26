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
	virtual void AddPickID(int id, int& next);
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
};
}
}

#endif MANIPULATOR_NODE_H