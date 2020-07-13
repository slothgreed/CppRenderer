#ifndef SAMPLE_MODEL_GENERATOR_H
#define SAMPLE_MODEL_GENERATOR_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT SampleModelGenerator
{
public:
	SampleModelGenerator();
	~SampleModelGenerator();

	static void BezierLine(RenderData* pVertexBuffer);
private:

};
}
}

#endif SAMPLE_MODEL_GENERATOR_H
