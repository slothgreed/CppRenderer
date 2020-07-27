#ifndef DEPTH_STATE_H
#define DEPTH_STATE_H

namespace KI
{
namespace Gfx
{


class DLL_EXPORT DepthState : public IPixOps
{
public:
	DepthState();
	~DepthState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_DEPTH; }

	void DepthTest(bool value);
	void DepthFunc(COMP_FUNC func);
	virtual void Bind() override;
	virtual void UnBind() override;
	virtual bool Compare(const IGLState& state) override;
private:
	bool m_depthTest;
	COMP_FUNC m_depthFunc;
};

}
}
#endif DEPTH_STATE_H