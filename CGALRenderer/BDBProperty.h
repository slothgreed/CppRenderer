#ifndef BDB_PROPERTY_H
#define BDB_PROEPRTY_H

namespace KI
{
class DefaultVertexBuffer;
class DefaultShader;
class BDBProperty : public IModelProperty
{
public:
	BDBProperty(const BDB& bdb);
	~BDBProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_BDB; }
	virtual void Draw();
	virtual void Update(void* bdb) override;
private:
	void GetBDBPosition(const BDB& bdb, vector<vec3>& position);
	void Build(const BDB& bdb);
	shared_ptr<IShader> m_pShader;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
};

}

#endif // !BDB_PROPERTY_H
