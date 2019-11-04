#ifndef SHADER_COMMON_H
#define SHADER_COMMON_H

#define SCENE_DATA_LOCATION 5

struct SceneData
{
	glm::mat4x4 Projection;
	glm::mat4x4 ViewMatrix;
};

#endif SHADER_COMMON_H