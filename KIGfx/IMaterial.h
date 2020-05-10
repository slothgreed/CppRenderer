#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT IMaterial : public IEmbeddedShaderCode
{
public:
	IMaterial() {};
	virtual ~IMaterial() {};

	virtual void FetchUniformLocation(GLuint programId) {};
	virtual void Bind() {};
	virtual void UnBind() {};
	virtual void GetEmbeddedCode(SHADER_PROGRAM_TYPE& type, string& code) {};
private:

};

}
}

#endif
