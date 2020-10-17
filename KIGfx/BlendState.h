#ifndef BLEND_STATE_H
#define BLEND_STATE_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT BlendState : public IGLState
{
public:
	BlendState();
	~BlendState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_BLEND; }

	void Enable(bool value);
	void BlendFunc(BLEND_FACTOR src, BLEND_FACTOR dst);
	virtual void Bind() override;
	virtual void UnBind() override;
	virtual bool Compare(const IGLState& state) override;
private:
	bool m_enable;
	BLEND_FACTOR m_Src;
	BLEND_FACTOR m_Dst;
};
}
}


#endif BLEND_STATE_H