#ifndef MODEL_GENERATOR_H
#define MODEL_GENERATOR_H
namespace KI
{
class VertexBuffer;
class ModelGenerator
{
public:
	ModelGenerator();
	~ModelGenerator();

	static void Axis(VertexBuffer* vertexBuffer);
	static void RenderPlane(VertexBuffer* vertexBuffer); // レンダリング用の平面

private:
};
}
#endif	