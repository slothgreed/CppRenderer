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
	void Generate();
	void Set(const SceneData& data);
	void Bind();
	void UnBind();
private:
	GLuint m_SceneId;
};
}
#endif UNIFORM_SCENE_H