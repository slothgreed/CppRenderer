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
	static void RenderPlane(DefaultVertexBuffer* vertexBuffer); // レンダリング用の平面
	static void CubeSpace(const BDB& size, DefaultVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer);
	// sectorNum : 横の分割数
	// stackNum : 縦の分割数
	static void Sphere(float radius, int sectorNum, int stackNum, DefaultVertexBuffer* pVertexBuffer, IndexBuffer* pIndexBuffer);
private:
};
}
}
#endif	