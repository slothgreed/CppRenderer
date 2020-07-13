#ifndef UNIFORM_SCENE_H
#define UNIFORM_SCENE_H

namespace KI
{
namespace ShaderLib
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
	void SetViewMatrix(const mat4x4& viewMatrix);
	void SetProjection(const mat4x4& projMatrix);
	virtual void Bind() override;
private:
	SceneData m_data;
};
}
}
#endif UNIFORM_SCENE_H