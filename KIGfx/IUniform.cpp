namespace KI
{
namespace Gfx
{

void UniformSet::Set(
	shared_ptr<IUniform> pVertex,
	shared_ptr<IUniform> pFrag)
{
	Set(pVertex, nullptr, nullptr, nullptr, pFrag);
}

void UniformSet::Set(
	shared_ptr<IUniform> pVertex,
	shared_ptr<IUniform> pGeometry,
	shared_ptr<IUniform> pFrag)
{
	Set(pVertex, nullptr, nullptr, pGeometry, pFrag);
}

void UniformSet::Set(
	shared_ptr<IUniform> pVertex,
	shared_ptr<IUniform> pTES,
	shared_ptr<IUniform> pTCS,
	shared_ptr<IUniform> pFrag)
{
	Set(pVertex, pTES, pTCS, nullptr, pFrag);
}

void UniformSet::Set(
	shared_ptr<IUniform> pVertex,
	shared_ptr<IUniform> pTES,
	shared_ptr<IUniform> pTCS,
	shared_ptr<IUniform> pGeometry,
	shared_ptr<IUniform> pFrag)
{
	m_pVertex	= pVertex;
	m_pTES		= pTES;
	m_pTCS		= pTCS;
	m_pGeometry = pGeometry;
	m_pFrag		= pFrag;
}

}
}