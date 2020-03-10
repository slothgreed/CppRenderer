#ifndef IPRIMITIVE_H
#define IPRIMITIVE_H

namespace KI
{
namespace Topology
{
class DLL_EXPORT IPrimitive
{
public:
	IPrimitive(int indexOffset = 0) { m_indexOffset = indexOffset; };
	~IPrimitive() {};

public:
	virtual vector<vec3>& Position() { return m_position; };
	virtual vector<vec3>& Normal() { return m_normal; };
	virtual vector<vec2>& Texcoord() { return m_texcoord; };
	virtual vector<int>& Index() { return m_index; };
	void Multi(const mat4x4& matrix);
	int IndexOffset() { return m_indexOffset; };
	void SetIndexOffset(int indexOffset) { m_indexOffset = indexOffset; };
protected:
	vector<vec3> m_position;
	vector<vec3> m_normal;
	vector<vec2> m_texcoord;
	int m_indexOffset;
	vector<int> m_index;
};
}
}

#endif
