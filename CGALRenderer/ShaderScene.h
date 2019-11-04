#ifndef SHADER_SCENE_H
#define SHADER_SCENE_H
struct SceneData;
class ShaderScene
{
public:
	ShaderScene();
	~ShaderScene();
	void Generate();
	void Set(const SceneData& data);
	void BindBlock(GLuint progmra);
	void Use();
private:
	GLuint m_SceneId;
	GLuint m_SceneBlockId;
};

#endif SHADER_SCENE_H