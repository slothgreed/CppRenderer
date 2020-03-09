#ifndef UNIFORM_SCENE_H
#define UNIFORM_SCENE_H

namespace KI
{
namespace Renderer
{
struct SceneData
{
	mat4x4 projection;
	mat4x4 viewMatrix;
};

class DLL_EXPORT UniformScene : public UniformBuffer
{
public:
	UniformScene();
	~UniformScene();
	void Set(const SceneData& data);
};
}
}
#endif UNIFORM_SCENE_H