#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Plane(RenderData* pRenderData, VERTEX_LAYOUT layout); // ƒŒƒ“ƒ_ƒŠƒ“ƒO—p‚Ì•½–Ê
	static void CubeSpace(const BDB& size, RenderData* pRenderData);
private:
};
}
}
#endif	