//precision lowp float;

//uniform vec3 edge_factor;
//uniform vec3 interior_factor;
//uniform vec3 fixColor;
in DataFrag {
	vec2 texcoord;
} frag;

out vec4 outColor;

void main() {
	bool a = abs(fract(frag.texcoord.x + 0.5) - 0.5) < 0.1;
	bool b = abs(fract(frag.texcoord.y + 0.5) - 0.5) < 0.1;
	if (a || b){
		outColor = vec4(0,1,0,1);
	}else{
		outColor = vec4(0,0,1,1);
	}
	
}
