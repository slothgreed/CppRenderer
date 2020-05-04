#ifndef GL_ITERATOR_H
#define GL_ITERATOR_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT GL_TRIANGLES_Iterator
{
public:
	// sourceType = GL_TRIANGLE_STRIP 
	GL_TRIANGLES_Iterator(GLuint sourceType, vec3* positions, int size);
	bool HasNext();
	void Current(vec3& pos0, vec3& pos1, vec3& pos2);
	void Next();
	int Index() { return m_index; }
	GLuint m_sourceType;
	vec3* m_position;
	int m_index;
	int m_size;
};

}

}

#endif