namespace KI
{
namespace Foundation
{
void MathHelper::SphericalToCartesian(float radius, float x, float y, vec3& result)
{
	result.x = radius * sin(y) * cos(x);
	result.y = radius * cos(y);
	result.z = radius * sin(y) * sin(x);

	//Logger::Output(LOG_LEVEL::DEBUG, to_string(x) + "," + to_string(y) + "\n");
	//float rad = 0;
	//CartesianToSpherical(result, rad, x, y);
	//Logger::Output(LOG_LEVEL::DEBUG, to_string(x) + "," + to_string(y) + "\n");
}

void MathHelper::CartesianToSpherical(const vec3& position, float& radian, float& theta, float& phi)
{
	radian = glm::length(position);
	phi = glm::acos(position.z / radian);
	theta = glm::atan(position.y / position.x);
}

float MathHelper::CalcTriangleArea(const vec3& v1, const vec3& v2, const vec3& v3)
{
	vec3 vector1 = v2 - v1;
	vec3 vector2 = v3 - v1;

	vec3 exterior = cross(vector1, vector2);

	float area = length(exterior) / 2;

	return area;
}

void MathHelper::CalcNormal(const vec3& v1, const vec3& v2, const vec3& v3, vec3& normal)
{
	vec3 vector1 = normalize(v2 - v1);
	vec3 vector2 = normalize(v3 - v1);

	normal = cross(vector1,vector2);
}

float MathHelper::CalcRadian(const vec3& v1, const vec3& v2) 
{
	vec3 vector1 = normalize(v1);
	vec3 vector2 = normalize(v2);

	float rad = dot(vector1, vector2);

	return acos(rad);
}

std::string MathHelper::ToString(const vec3& value)
{
	// (x, y, z)
	string str;
	str += "(";
	str += to_string(value.x) + ", ";
	str += to_string(value.y) + ", ";
	str += to_string(value.z) + ")";

	return str;
}
}
}