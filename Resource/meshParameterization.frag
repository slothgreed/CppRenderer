#version 330
precision lowp float;

uniform vec3 edge_factor;
uniform vec3 interior_factor;

in fData {
	vec2 texcoord;
	vec4 color;
} frag;

out vec4 outColor;

void main() {
	vec3 finalColor = vec3(1,0,0) * (1-frag.color.a) + frag.color.rgb * frag.color.a;
	bool a = abs(fract(frag.texcoord.x + 0.5) - 0.5) < 0.1;
	bool b = abs(fract(frag.texcoord.y + 0.5) - 0.5) < 0.1;
	if (a || b)
		finalColor *= edge_factor;
	else
		finalColor *= interior_factor;

	outColor = vec4(finalColor, 1.0);
}
