#ifndef GL_ARRAY_H
#define	GL_ARRAY_H

namespace KI
{
namespace Gfx
{

class DLL_EXPORT GLArray
{
public:
	GLArray();
	~GLArray();
	int GetInt(int index);
	float GetFloat(int index);
	void* Data();
	int GetSize();
	vec2 GetVector2(int index);
	vec3 GetVector3(int index);
	vec4 GetVector4(int index);
	void NewArray(GLenum dataType, int dataSize, int arraySize);

private:

	void* m_data;
	GLenum m_dataType;
	int m_dataSize;
	int m_arraySize;
};

}
}

#endif GL_ARRAY_H

