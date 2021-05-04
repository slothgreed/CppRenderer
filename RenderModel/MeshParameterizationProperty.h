#ifndef MESH_PARAMETERIZATION_PROPERTY_H
#define MESH_PARAMETERIZATION_PROPERTY_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT MeshParameterizationPropertyArgs : public IRenderModelPropertyArgs
{
public:

	MeshParameterizationPropertyArgs() : m_level(0) {};
	MeshParameterizationPropertyArgs(int level) : m_level(level){};
	~MeshParameterizationPropertyArgs() {};
	virtual PROPERTY_TYPE PropertyType() { return PROPERTY_TYPE_MESH_PARAMETERIZATION; };

	int Level() { return m_level; }
private:
	int m_level;
};

class MeshParameterizationProperty : public IRenderModelProperty
{
public:
	MeshParameterizationProperty();
	~MeshParameterizationProperty();

	virtual PROPERTY_TYPE PropertyType() override { return PROPERTY_TYPE_MESH_PARAMETERIZATION; }
	virtual void BuildCore(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Update(IModelNode* pModel, IPropertyArgs* pPropertyArgs) override;
	virtual void Draw(shared_ptr<UniformStruct> pUniform);
	virtual void Update(void* sender, IEventArgs* pArgs);
	virtual void InitializeUI();
	virtual void ShowUI();

	struct UI
	{
		SliderIntUI level;
	};
private:
	struct GPUBuffer
	{
		shared_ptr<ArrayBuffer> positionBuffer;
		shared_ptr<ArrayBuffer> normalBuffer;
		shared_ptr<ArrayBuffer> tangentBuffer;
		shared_ptr<ArrayBuffer> uvBuffer;
	};

	void BuildVBO(IModelNode* pModelNode, MeshParameterizationPropertyArgs* pPropertyArgs);
	GPUBuffer m_ArrayBuffers;
	shared_ptr<VertexBuffer> m_pVertexBuffer;
	shared_ptr<RenderData> m_pRenderData;
	shared_ptr<TangentVisualizeShading> m_pShading;
	shared_ptr<HalfEdgeModel> GetHalfEdgeModel();

	UI m_ui;
};

}
}
#endif MESH_PARAMETERIZATION_PROPERTY_H