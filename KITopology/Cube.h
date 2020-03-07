namespace KI
{
namespace Topology
{
class DLL_EXPORT CubeArgs
{
public:
	CubeArgs() : min(), max(){};
	~CubeArgs() {};
	vec3 min;
	vec3 max;
};
class DLL_EXPORT Cube : public IPrimitive
{
public:
	Cube(int indexOffset);
	Cube();
	~Cube();

	void Build(const CubeArgs& args);
private:
	void AddTrianlgeIndexFromRectangle(int index, int vertex0, int vertex1, int vertex2, int vertex3);

};
}
}