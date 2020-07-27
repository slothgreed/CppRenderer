#ifndef CULL_STATE_H
#define CULL_STATE_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT CullState : public IRasterState
{
public:
	CullState();
	~CullState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_CULL; }

	void CullEnable(bool value) { m_cullFace = value; };
	void FrontFace(FRONT_FACE func) { m_frontFace = func; };
	void CullFace(CULL_MODE func) { m_cullMode = func; };
	virtual void Bind() override;
	virtual void UnBind() override;
	virtual bool Compare(const IGLState& state) override;
private:
	bool m_cullFace;
	FRONT_FACE m_frontFace;
	CULL_MODE m_cullMode;
};

}
}
#endif CULL_STATE_H