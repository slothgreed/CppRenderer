#ifndef BDB_PROPERTY_H
#define BDB_PROEPRTY_H

namespace KI
{
class VertexBuffer;
class DefaultShader;
class BDBProperty : public IModelProperty
{
public:
	BDBProperty(BDB& bdb);
	~BDBProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_BDB; }
	void GenVBO();
	virtual void Draw();

private:
	IShader* m_pShader;
	VertexBuffer* m_pVertexBuffer;
	BDB m_bdb;
};

}

#endif // !BDB_PROPERTY_H
