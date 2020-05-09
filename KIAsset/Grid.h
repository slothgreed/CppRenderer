namespace KI
{
namespace Asset
{

class DLL_EXPORT GridArgs
{
public:
	GridArgs(const vec3& size, const vec3& gap) { m_size = size, m_gap = gap; }
	~GridArgs();
	vec3 m_size;
	vec3 m_gap;
};
class DLL_EXPORT Grid
{
public:
	Grid(const GridArgs& args);
	~Grid();

	void Build(const GridArgs& args);

};


}
}