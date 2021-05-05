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

	virtual void ClearSelect() override;
	virtual void AddSelect(PICK_TYPE type, shared_ptr<IShading> pShading, int index, int first, int count) override;
	virtual void FixedShaderDraw(shared_ptr<IShader> pShader, shared_ptr<IShading> pShading, shared_ptr<UniformStruct> pUniformStorage);
	virtual void Draw(shared_ptr<UniformStruct> pUniform);

private:
	virtual void SetPickID(int start, int* next);
	virtual bool HasPickID(int index);

	void GenManipulatorHandleVBO(
		RenderData& pFaceData,
		MANIPULATOR_HANDLE handle);
	void SetRenderData();
	RenderData m_pManipulatorData[3];
	MANIPULATOR_TYPE m_ManipulatorType;
	shared_ptr<IManipulatorModel> m_pManipulator;
	shared_ptr<BasicShading> m_pShading;
	int m_SelectIndex;
};
}
}

#endif MANIPULATOR_NODE_H