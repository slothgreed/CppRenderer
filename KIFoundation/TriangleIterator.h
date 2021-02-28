#ifndef TRIANGLE_ITERATOR_H
#define TRIANGLE_ITERATOR_H

namespace KI
{
namespace Foundation
{
// use case 
// TrianlgeIterator itr;
// while(itr.HasNext()){
//   itr.Current(pos0,pos1,pos2);
//	 ...
//   itr.Next();
// }
class DLL_EXPORT TriangleIterator
{
public:
	enum TriangleType
	{
		TRIANGLES,
		TRIANGLE_STRIP
	};

	// sourceType = GL_TRIANGLE_STRIP 
	TriangleIterator(unsigned int sourceType, const vec3* positions, const int* indexs, size_t size);
	TriangleIterator(TriangleType sourceType, const vec3* positions, const int* indexs, size_t size);
	bool HasNext();
	void Current(vec3* pos0, vec3* pos1, vec3* pos2);
	void Next();
	int TriangleSize();
	int Index() { return m_index; }
	TriangleType m_sourceType;
	const vec3* m_position;
	const int* m_indexList;
	int m_index;
	int m_size;
};

}

}

#endif