#ifndef IPFX_EFFECT_H
#define IPFX_EFFECT_H
class IPfxEffect
{
public:
	IPfxEffect() {};
	~IPfxEffect() {};

	virtual void Initialize() = 0;
	virtual void Draw() = 0;
	virtual void Resize(int width, int height) = 0;
private:

};
#endif IPFX_EFFECT_H