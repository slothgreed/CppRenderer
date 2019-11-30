#ifndef UNIFORM_SCENE_H
#define UNIFORM_SCENE_H

namespace KI
{
#define SCENE_DATA_LOCATION 5
struct SceneData
{
	glm::mat4x4 Projection;
	glm::mat4x4 ViewMatrix;
};

class UniformScene : public UniformBuffer
{
public:
	UniformScene();
	~UniformScene();
	virtual void Generate() override;
	virtual void Bind() override;
	virtual void UnBind() override;
	virtual void Dispose() override;
	void Set(const SceneData& data);

private:
	GLuint m_SceneId;
};
}
#endif UNIFORM_SCENE_H