#ifndef PRIMITIVE_MODEL_H
#define PRIMITIVE_MODEL_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT PrimitiveModel : public IModel
{
public:
	PrimitiveModel(shared_ptr<IPrimitive> pPrimitiveModel);
	~PrimitiveModel() {};

	virtual MODEL_TYPE Type() { return MODEL_TYPE_PRIMITIVE; };
	virtual void GetFaceList(vector<vec3>& position, vector<vec3>& normal, vector<vec3>& color, vector<vec2>& texcoord);
	virtual void GetFaceIndexList(vector<int>& index);

	shared_ptr<IPrimitive> GetPrimitive() { return m_pPrimitive; };

	void RaycastPick(RaycastPickInfo& result);
	virtual void GetBDB(BDB& bdb) {};

private:
	shared_ptr<IPrimitive> m_pPrimitive;
};



}
}


#endif PRIMITIVE_MODEL_H
