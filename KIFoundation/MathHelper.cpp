namespace KI
{
namespace Foundation
{
void MathHelper::SphericalToCartesian(float radius, float x, float y, vec3& result)
{
	result.x = radius * sin(y) * cos(x);
	result.y = radius * cos(y);
	result.z = radius * sin(y) * sin(x);

	//Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, to_string(x) + "," + to_string(y) + "\n");
	//float rad = 0;
	//CartesianToSpherical(result, rad, x, y);
	//Logger::Output(LOG_LEVEL::LOG_LEVEL_DEBUG, to_string(x) + "," + to_string(y) + "\n");
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

float MathHelper::ToRadian(float angle)
{
	return angle * glm::pi<float>() / 180;
}

float MathHelper::ToAngle(float rad)
{
	return rad * 180 / glm::pi<float>();
}

float MathHelper::CramesDet(vec3 a, vec3 b, vec3 c)
{
	return (
		  (a.x * b.y * c.z)
		+ (a.y * b.z * c.x)
		+ (a.z * b.x * c.y)
		- (a.x * b.z * c.y)
		- (a.y * b.x * c.z)
		- (a.z * b.y * c.x));
}

ivec4 MathHelper::WorldToScreenPos(const mat4x4& proj, const mat4x4& view, const mat4x4& model, const vec3& value)
{
	vec4  result = proj * view * model * vec4(value.x, value.y, value.z, 1.0);

	return result / result.w;
}

string MathHelper::ToString(const vec2& value)
{
	// (x, y)
	string str;
	str += "(";
	str += to_string(value.x) + ", ";
	str += to_string(value.y) + ") ";

	return str;
}
string MathHelper::ToString(const ivec4& value)
{
	// (x, y, z, w)
	string str;
	str += "(";
	str += to_string(value.x) + ", ";
	str += to_string(value.y) + ", ";
	str += to_string(value.z) + ",";
	str += to_string(value.w) + ")";

	return str;
}
string MathHelper::ToString(const vec3& value)
{
	// (x, y, z)
	string str;
	str += "(";
	str += to_string(value.x) + ", ";
	str += to_string(value.y) + ", ";
	str += to_string(value.z) + ")";

	return str;
}

string MathHelper::ToString(const mat4x4& value)
{
	// (,,)
	string str;
	str += "(";
	str += to_string(value[0][0]) + ", " + to_string(value[0][1]) + ", " + to_string(value[0][2]) + ", " + to_string(value[0][3]) + "\n";
	str += to_string(value[1][0]) + ", " + to_string(value[1][1]) + ", " + to_string(value[1][2]) + ", " + to_string(value[1][3]) + "\n";
	str += to_string(value[2][0]) + ", " + to_string(value[2][1]) + ", " + to_string(value[2][2]) + ", " + to_string(value[2][3]) + "\n";
	str += to_string(value[3][0]) + ", " + to_string(value[3][1]) + ", " + to_string(value[3][2]) + ", " + to_string(value[3][3]) + ")";

	return str;
}
}
}