#ifndef VECTOR_PROPERTY_H
#define VECTOR_PROPERTY_H

namespace KI
{

class VectorProperty : IModelProperty
{
public:
	VectorProperty(const vector<vec3>& vectorList, const vec3& color);
	~VectorProperty();

	virtual PROPERTY_TYPE Type() override { return PROPERTY_TYPE_VECTOR; }
private:
	void GenVBO(const vector<vec3>& vertexList, const vec3& color);
	shared_ptr<IShader> m_pShader;
	shared_ptr<VertexBuffer> m_pVertexBuffer;
	
};

}


#endif // !VECTOR_PROPERTY_H

