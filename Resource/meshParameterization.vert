
layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec3 a_tangent;
layout(location = 3) in vec3 a_uv;

out DataVert {
	vec3 normal;
	vec3 tangent;
	vec3 uv;
} vert;

void main() {
	gl_Position = vec4(a_position, 1.0);
	vert.normal = a_normal;
	vert.tangent = a_tangent;
	vert.uv = a_uv;
}
