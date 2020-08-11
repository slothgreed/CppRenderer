#ifndef IPRIMITIVE_H
#define IPRIMITIVE_H

namespace KI
{
namespace Topology
{
class DLL_EXPORT IPrimitive
{
public:
	IPrimitive(int indexOffset = 0);
	~IPrimitive() {};

public:
	GLuint GetDrawType();
	virtual vector<vec3>& Position() { return m_position; };
	virtual vector<vec3>& Normal() { return m_normal; };
	virtual vector<vec3>& Color() { return m_color; };
	virtual vector<vec2>& Texcoord() { return m_texcoord; };
	virtual vector<int>& Index() { return m_index; };
	void Multi(const mat4x4& matrix);
	void SetIndexOffset(int indexOffset) { m_indexOffset = indexOffset; };
	void SetIndexOffset(size_t indexOffset) { m_indexOffset = (int)indexOffset; };
	int IndexOffset() { return m_indexOffset; };
protected:

	GLuint m_drawType;
	vector<vec3> m_position;
	vector<vec3> m_normal;
	vector<vec3> m_color;
	vector<vec2> m_texcoord;
	int m_indexOffset;
	vector<int> m_index;
};
}
}

#endif
