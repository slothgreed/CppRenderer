#ifndef SAMPLER_H
#define SAMPLER_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT Sampler : public GLObject
{
public:
	Sampler();
	~Sampler();

	virtual void Bind();
	virtual void Generate();
	virtual void UnBind();
	virtual void Dispose();
private:

};
}
}
#endif // !SAMPLER_H