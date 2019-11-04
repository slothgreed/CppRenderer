
void MathHelper::SphericalToCartesian(float x, float y, vec3& result)
{
	result.x = sin(y) * cos(x);
	result.y = cos(y);
	result.z = sin(y) * sin(x);

	//Logger::Output(LOG_LEVEL::DEBUG, to_string(x) + "," + to_string(y) + "\n");
	//float rad = 0;
	//CartesianToSpherical(result, rad, x, y);
	//Logger::Output(LOG_LEVEL::DEBUG, to_string(x) + "," + to_string(y) + "\n");
}

void MathHelper::CartesianToSpherical(const glm::vec3& position, float& radian, float& theta, float& phi)
{
	radian = glm::length(position);
	phi = glm::acos(position.z / radian);
	theta = glm::atan(position.y / position.x);
}