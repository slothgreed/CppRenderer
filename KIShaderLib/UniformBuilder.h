#ifndef UNIFORM_BUILDER_H
#define UNIFORM_BUILDER_H

namespace KI
{
namespace ShaderLib
{

class DLL_EXPORT UniformBuilder
{
public:
	shared_ptr<UniformStruct> BuildStruct();
	shared_ptr<UniformLight> BuildLight();
	shared_ptr<UniformMaterial> BuildMaterial();
	shared_ptr<UniformModel> BuildModel();
	shared_ptr<UniformScene> BuildScene();
};
}
}

#endif UNIFORM_BUILDER_H
