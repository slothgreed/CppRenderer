#include "common\common.h"
#include "common\struct.h"
out vec4 outputColor;

#ifdef IN_TEXTURE
uniform sampler2D uTexture0;
in Data{
	in vec3 position;
	in vec3 normal;
	in vec2 texcoord;
}InData;
#endif

#ifdef IN_COLOR
in Data{
	in vec3 position;
	in vec3 normal;
	in vec4 color;
}InData;
#endif

#ifdef IN_FIXCOLOR
uniform vec4 uFixColor;
in Data{
	in vec3 position;
	in vec3 normal;
}InData;
#endif

vec4 GetColor()
{
#if defined(IN_TEXTURE)
	return texture2D(uTexture0,InData.texcoord);
#elif defined(IN_COLOR)
	return InData.color;
#elif defined(IN_FIXCOLOR)
	return uFixColor;
#endif
}

vec4 Phong(vec4 color)
{
	// ambient;
	vec3 ambient = material.Ambient.xyz * light.Ambient.xyz;
	
	// diffuse;
	float diffDot = max(dot(InData.normal,light.Position.xyz),0.0);
	vec3 diffuse = material.Diffuse.xyz * light.Diffuse.xyz * diffDot;
	
	// specular;
	vec3 normal = normalize(model.NormalMatrix * InData.normal);
	vec3 position = normalize(-InData.position.xyz);
	vec3 s = normalize(vec3(light.Position.xyz - position.xyz));
	vec3 v = normalize(-position.xyz);
	vec3 r = reflect(-s, normal);
	vec3 specular = light.Specular.xyz * material.Specular.xyz * 
					pow(max(dot(r,v),0.0),material.Shinning);
	
	return vec4(ambient + diffuse, 1.0) * color + vec4(specular,1.0);
}

void main()
{
	outputColor = Phong(GetColor());
}