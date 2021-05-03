precision lowp float;

uniform vec3 edge_factor;
uniform vec3 interior_factor;
uniform vec3 fixColor;
in Data {
	vec2 texcoord;
} InData;

out vec4 outColor;

void main() {
	bool a = abs(fract(InData.texcoord.x + 0.5) - 0.5) < 0.1;
	bool b = abs(fract(InData.texcoord.y + 0.5) - 0.5) < 0.1;
	if (a || b){
		//outColor = fixColor * edge_factor;
		outColor = vec4(0.5,0.5,0.5,1) * vec4(0,1,0,1);
	}else{
		//outColor = fixColor * interior_factor;
		outColor = vec4(0.5,0.5,0.5,1) * vec4(0,0,1,1);
	}
}
