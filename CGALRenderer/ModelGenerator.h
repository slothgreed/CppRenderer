#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
class DefaultVertexBuffer;
class ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Axis(DefaultVertexBuffer* vertexBuffer);
	static void RenderPlane(DefaultVertexBuffer* vertexBuffer); // レンダリング用の平面

private:
};
}
#endif	