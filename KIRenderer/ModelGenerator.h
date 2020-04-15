#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
namespace Renderer
{
class RenderData;
class DLL_EXPORT ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Axis(RenderData* pRenderData);
	static void RenderPlane(RenderData* pRenderData); // ƒŒƒ“ƒ_ƒŠƒ“ƒO—p‚Ì•½–Ê
	static void CubeSpace(const BDB& size, RenderData* pRenderData);
	// sectorNum : ‰¡‚Ì•ªŠ„”
	// stackNum : c‚Ì•ªŠ„”
	static void Sphere(float radius, int sectorNum, int stackNum, RenderData* pRenderData);
private:
};
}
}
#endif	