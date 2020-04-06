#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
namespace Renderer
{
class DefaultVertexBuffer;
class DLL_EXPORT ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Axis(DefaultVertexBuffer* vertexBuffer);
	static void RenderPlane(DefaultVertexBuffer* vertexBuffer); // ƒŒƒ“ƒ_ƒŠƒ“ƒO—p‚Ì•½–Ê
	static void CubeSpace(const BDB& size, DefaultVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer);
	// sectorNum : ‰¡‚Ì•ªŠ„”
	// stackNum : c‚Ì•ªŠ„”
	static void Sphere(float radius, int sectorNum, int stackNum, DefaultVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer);
private:
};
}
}
#endif	