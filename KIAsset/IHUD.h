#ifndef IHUD_H
#define IHUD_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT IHUD : public IPrimitive
{
public:
	IHUD();
	~IHUD();

	virtual void SetWindowPosition(int top, int left);
private:
	ivec2 m_windowPosition;
};

}
}
#endif IHUD_H