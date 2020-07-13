namespace KI
{
namespace ShaderLib
{
shared_ptr<UniformStruct> UniformBuilder::BuildStruct()
{
	return make_shared<UniformStruct>();
}
shared_ptr<UniformLight> UniformBuilder::BuildLight()
{
	return make_shared<UniformLight>();
}
shared_ptr<UniformMaterial> UniformBuilder::BuildMaterial()
{
	return make_shared<UniformMaterial>();
}
shared_ptr<UniformModel> UniformBuilder::BuildModel()
{
	return make_shared<UniformModel>();
}
shared_ptr<UniformScene> UniformBuilder::BuildScene()
{
	return make_shared<UniformScene>();
}
}
}