#ifndef IPRIMITIVE_H
#define IPRIMITIVE_H

namespace KI
{

class IPrimitive
{
public:
	IPrimitive() {};
	~IPrimitive() {};

public:
	virtual vector<vec3>& Position() { return m_position; };
	virtual vector<vec3>& Normal() { return m_normal; };
	virtual vector<vec2>& Texcoord() { return m_texcoord; };
	virtual vector<int>& Index() { return m_index; };
	void Multi(const mat4x4& matrix);
protected:
	vector<vec3> m_position;
	vector<vec3> m_normal;
	vector<vec2> m_texcoord;
	vector<int> m_index;
};
}

#endif
