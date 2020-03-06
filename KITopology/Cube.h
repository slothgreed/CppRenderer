namespace KI
{
namespace Topology
{
class DLL_EXPORT Cube : public IPrimitive
{
public:
	Cube(int indexOffset);
	Cube();
	~Cube();

	void Build(const vec3& min, const vec3& max);
private:
	void AddTrianlgeIndexFromRectangle(int index, int vertex0, int vertex1, int vertex2, int vertex3);

};
}
}