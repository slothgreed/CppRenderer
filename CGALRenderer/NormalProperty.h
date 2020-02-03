#ifndef NORMAL_PROPERTY_H
#define NORMAL_PROPERTY_H

namespace KI
{

// 法線プロパティ
class NormalProperty : public IModelProperty
{
public:
	NormalProperty();
	~NormalProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_VECTOR; }
	virtual void Draw();
	virtual void Update(IModel* pModel);
private:
	void Build(IModel* pModel);
	void SetVBOData(IModel* pModel);
	shared_ptr<IShader> m_pShader;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
	
};

}


#endif // !VECTOR_PROPERTY_H

