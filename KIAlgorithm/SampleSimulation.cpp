
namespace KI
{
namespace Algorithm
{

float h_U(const vec3& n, float time)
{
	return 
		-2.0f * (float)cos(pi<float>() * time / 8.0f) *	
		(float)sin(pi<float>() * n.x) * 
		(float)sin(pi<float>() * n.x) * 
		(float)cos(pi<float>() * n.y) *
		(float)sin(pi<float>() * n.y);
}

float h_V(const vec3& n, float time)
{
	return
		2.0f * (float)cos(pi<float>() * time / 8.0f) *
		(float)cos(pi<float>() * n.x) *
		(float)sin(pi<float>() * n.x) *
		(float)sin(pi<float>() * n.y) *
		(float)sin(pi<float>() * n.y);
}

// ref : GPUï¿óÒê}å`èàóùì¸ñÂ
void SampleSimulation::RungeKutta(const vec3& position, float time, float dt, vec3& result)
{
	float p[4];
	float q[4];
	vec3 pos;
	float t;

	// 1 
	p[0] = h_U(position, time);
	q[0] = h_V(position, time);

	// 2
	pos.x = position.x + 0.5f * p[0] * dt;
	pos.y = position.y + 0.5f * q[0] * dt;
	t = time + 0.5f * dt;
	p[1] = h_U(pos, t);
	q[1] = h_V(pos, t);

	// 3
	pos.x = position.x + 0.5f * p[1] * dt;
	pos.y = position.y + 0.5f * q[1] * dt;
	t = time + 0.5f * dt;
	p[2] = h_U(pos, t);
	q[2] = h_V(pos, t);

	// 4
	pos.x = position.x + p[2] * dt;
	pos.y = position.y + q[2] * dt;
	t = time + dt;
	p[3] = h_U(pos, t);
	q[3] = h_V(pos, t);

	result.x = position.x + ((p[0] + p[1] + p[2] + p[3]) / 6.0f) * dt;
	result.y = position.y + ((q[0] + q[1] + q[2] + q[3]) / 6.0f) * dt;

}
}
}