
layout(location=0) in vec3 a_position;
layout(location=1) in vec3 a_normal;
layout(location=2) in vec3 a_tangent;
layout(location=3) in vec3 a_uv;

out Data {
	vec3 normal;
	vec3 tangent;
	vec3 uv;
} OutData;

void main() {
	gl_Position = vec4(a_position, 1.0);
	OutData.normal = a_normal;
	OutData.tangent = a_tangent;
	OutData.uv = a_uv;
}
