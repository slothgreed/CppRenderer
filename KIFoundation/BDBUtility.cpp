namespace KI
{
namespace Foundation
{
mat4x4 BDBUtility::GetModelMatrixFromMin(const BDB& bdb)
{
	vec3 scale = bdb.Max();
	vec3 translate = bdb.Min();
	mat4x4 matrix(1);
	matrix = glm::scale(matrix, scale);
	matrix = glm::translate(matrix, translate);
	return matrix;
}
}
}