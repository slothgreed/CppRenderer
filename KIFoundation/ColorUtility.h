#ifndef COLOR_UTILITY_H
#define COLOR_UTILITY_H

namespace KI
{
namespace Foundation
{
class DLL_EXPORT ColorUtility
{
public:
	ColorUtility();
	~ColorUtility();

	static vec3 IndexToColor(int index);
	static vec3 GetPseudoColor(float value, float min, float max);
private:
	static void InitializePseudoColor();

	static std::vector<vec3> m_pseudoColor;
};
}
}


#endif COLOR_UTILITY_H