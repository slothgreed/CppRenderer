#ifndef IUNIFORM_H
#define IUNIFORM_H
namespace KI
{
class IUniform
{
public:
	IUniform() {};
	~IUniform() {};

	virtual SHADER_TYPE Type() = 0;
private:

};
}

#endif ISHADER_H


