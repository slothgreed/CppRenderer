#ifndef BUFFER_STATE_H
#define BUFFER_STATE_H

namespace KI
{
namespace Gfx
{
class DLL_EXPORT BufferState : public IGLState
{
public:
	BufferState();
	~BufferState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_CULL; }

	void ClearColor(const vec4& value) { m_clearcolor = value; };
	virtual void Bind() override;
	virtual void UnBind() override;
	virtual bool Compare(const IGLState& state) override;
private:
	vec4 m_clearcolor;
};

}
}
#endif BUFFER_STATE_H