namespace KI
{
namespace Asset
{

class DLL_EXPORT GridArgs
{
public:
	GridArgs(const vec2& size, vec2 interval) { m_size = size, m_Interval = interval; }
	~GridArgs() {};
	vec2 m_size;
	vec2 m_Interval;
};
class DLL_EXPORT Grid : public IPrimitive
{
public:
	Grid(const GridArgs& args);
	~Grid();

	void Build(const GridArgs& args);

};


}
}