#ifndef IUNIFORM_H
#define IUNIFORM_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT IUniform
{
public:
	IUniform() {};
	~IUniform() {};

	virtual SHADER_TYPE Type() = 0;
	virtual bool ShaderDefineComare(IUniform* pUniform) = 0;

private:

};

class DLL_EXPORT UniformSet
{
public:

	UniformSet() {};
	~UniformSet() {};


	shared_ptr<IUniform> Vertex() { return m_pVertex; }
	shared_ptr<IUniform> TES() { return m_pTES; }
	shared_ptr<IUniform> TCS() { return m_pTCS; }
	shared_ptr<IUniform> Geometry() { return m_pGeometry; }
	shared_ptr<IUniform> Frag() { return m_pFrag; }

	void Set(
		shared_ptr<IUniform> pVertex,
		shared_ptr<IUniform> pFrag) ;

	void Set(
		shared_ptr<IUniform> pVertex,
		shared_ptr<IUniform> pGeometry,
		shared_ptr<IUniform> pFrag);

	void Set(
		shared_ptr<IUniform> pVertex,
		shared_ptr<IUniform> pTES,
		shared_ptr<IUniform> pTCS,
		shared_ptr<IUniform> pFrag);

	void Set(
		shared_ptr<IUniform> pVertex,
		shared_ptr<IUniform> pTES,
		shared_ptr<IUniform> pTCS,
		shared_ptr<IUniform> pGeometry,
		shared_ptr<IUniform> pFrag);
	
private:
	shared_ptr<IUniform> m_pVertex;
	shared_ptr<IUniform> m_pTES;
	shared_ptr<IUniform> m_pTCS;
	shared_ptr<IUniform> m_pGeometry;
	shared_ptr<IUniform> m_pFrag;
};
}
}

#endif ISHADER_H


