#ifndef GRAY_SCALE_EFFECT_H
#define GRAY_SCALE_EFFECT_H

namespace KI
{

class GrayScaleEffect : public IPfxEffect
{
public:
	GrayScaleEffect();
	~GrayScaleEffect();

	virtual void Initialize() override;
	virtual void Draw() override;
private:

};
}


#endif GRAY_SCALE_EFFECT_H