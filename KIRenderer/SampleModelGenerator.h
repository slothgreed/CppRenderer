#ifndef SAMPLE_MODEL_GENERATOR_H
#define SAMPLE_MODEL_GENERATOR_H

namespace KI
{
namespace Renderer
{
class DefaultVertexBuffer;
class DLL_EXPORT SampleModelGenerator
{
public:
	SampleModelGenerator();
	~SampleModelGenerator();

	static void BezierLine(DefaultVertexBuffer* pVertexBuffer);
private:

};
}
}

#endif SAMPLE_MODEL_GENERATOR_H
