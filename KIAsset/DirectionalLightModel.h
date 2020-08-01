#ifndef DIRECTIONAL_LIGHT_MODEL_H
#define DIRECTIONAL_LIGHT_MODEL_H
namespace KI
{
namespace Asset
{

class DLL_EXPORT DirectionalLightModel : public IPrimitive
{
public:
	DirectionalLightModel();
	~DirectionalLightModel();

private:
	void Build();

};

}
}

#endif DIRECTIONAL_LIGHT_MODEL_H
