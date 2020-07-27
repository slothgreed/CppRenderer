#ifndef POLYGON_STATE_H
#define POLYGON_STATE_H

namespace KI
{
namespace Gfx
{

class DLL_EXPORT PolygonState : public IPixOps
{
public:
	PolygonState();
	~PolygonState();

	virtual const STATE_TYPE Type() const { return STATE_TYPE_POLYGON; }

	void OffsetFill(bool value) { m_offsetFill = value; };
	void Offset(float factor, float units) { m_factor = factor; m_units = units; }
	virtual void Bind() override;
	virtual void UnBind() override;
	virtual bool Compare(const IGLState& state) override;
private:
	bool m_offsetFill;
	float m_factor;
	float m_units;
};

}
}
#endif DEPTH_STATE_H