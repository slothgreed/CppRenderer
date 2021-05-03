#include "common\struct.h"

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in DataVert {
	vec3 normal;
	vec3 tangent;
	vec3 uv;
} vert[];

out DataFrag {
	vec2 texcoord;
} frag;


vec3 compat_orientation(vec3 q, vec3 ref, vec3 n) {
	vec3 t = cross(n, q);
	float dp0 = dot(q, ref), dp1 = dot(t, ref);
	if (abs(dp0) > abs(dp1))
		return q * sign(dp0);
	else
		return t * sign(dp1);
}

vec3 compat_position(vec3 o, vec3 ref, vec3 q, vec3 t, vec3 n) {
	vec3 d = ref - o;
	return o +
	   q * -round(dot(q, d) * -1) +
	   t * -round(dot(t, d) * -1);

	// return o +
	//   q * round(dot(q, d) * inv_scale) * scale +
	//  t * round(dot(t, d) * inv_scale) * scale;
}

void main2() {
	frag.texcoord = vec2(1,0);
	gl_Position = scene.Projection * scene.ViewMatrix * model.ModelMatrix * gl_in[0].gl_Position;
	EmitVertex();
	
	frag.texcoord = vec2(1,0);

	gl_Position = scene.Projection * scene.ViewMatrix * model.ModelMatrix * gl_in[1].gl_Position;
	EmitVertex();
	
	frag.texcoord = vec2(1,0);
	gl_Position = scene.Projection * scene.ViewMatrix * model.ModelMatrix * gl_in[2].gl_Position;
	EmitVertex();
	EndPrimitive();
}

void main() {
	vec3 face_normal = normalize(cross(
		gl_in[1].gl_Position.xyz-gl_in[0].gl_Position.xyz,
		gl_in[2].gl_Position.xyz-gl_in[0].gl_Position.xyz));

	vec2 texcoord[3];
	/* Step 1: Rotate everthing into the triangle plane */
	vec3 tangents[3], uv[3];
	for (int i=0; i<3; ++i) {
		float cosTheta = dot(vert[i].normal, face_normal);

		if (cosTheta < 0.9999f) {
			vec3 axis = cross(vert[i].normal, face_normal);
			float sinTheta2 = dot(axis, axis);
			float factor = (1.0 - cosTheta) / sinTheta2;

			vec3 v_tangent = vert[i].tangent;
			tangents[i] = v_tangent * cosTheta + cross(axis, v_tangent)	+ axis * dot(axis, v_tangent) * factor;

			vec3 v_uv = vert[i].uv - gl_in[i].gl_Position.xyz;
			uv[i] = v_uv * cosTheta + cross(axis, v_uv)	+ axis * dot(axis, v_uv) * factor + gl_in[i].gl_Position.xyz;
		} else {
			tangents[i] = vert[i].tangent;
			uv[i] = vert[i].uv;
		}
	}

	/* Step 2: search orientation field quotient space */
	for (int i=1; i<3; ++i)
		tangents[i] = compat_orientation(tangents[i], tangents[0], face_normal);

	vec3 bitangents[3];
	for (int i=0; i<3; ++i)
		bitangents[i] = cross(face_normal, tangents[i]);

	/* Step 3: search position field quotient space */
	for (int i=1; i<3; ++i)
		uv[i] = compat_position(uv[i], uv[0], tangents[i], bitangents[i], face_normal);

	/* Step 4: compute uv coordinates */
	for (int i=0; i<3; ++i) {
		vec3 rel = gl_in[i].gl_Position.xyz - uv[i];
		texcoord[i] = vec2(-dot(rel, tangents[i]), -dot(rel, bitangents[i]));
		
		//texcoord[i] = vec2(
		//	dot(rel, tangents[i]) * inv_scale,
		//	dot(rel, bitangents[i]) * inv_scale
		//);
	}

	for (int i=0; i<3; ++i) {
		gl_Position = scene.Projection * scene.ViewMatrix * model.ModelMatrix * gl_in[i].gl_Position;
		frag.texcoord = texcoord[i];
		EmitVertex();
	}
	EndPrimitive();
}
