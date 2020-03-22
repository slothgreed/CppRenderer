namespace KI
{
namespace Renderer
{

NormalVisualizeShader::NormalVisualizeShader()
{
	SetVersion(GLSL_VERSION_400_CORE);
	SetVertexPath(string(SHADER_DIRECTORY) + "\\default.vert");
	SetGeomPath(string(SHADER_DIRECTORY) + "normalvisualize.geom");
	SetFragPath(string(SHADER_DIRECTORY) + "default.geom");
	
}

NormalVisualizeShader::~NormalVisualizeShader()
{
}

}
}