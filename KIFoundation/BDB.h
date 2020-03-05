#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT BDB
{
public:
	BDB();
	BDB(glm::vec3 min, glm::vec3 max);
	void Set(glm::vec3 min, glm::vec3 max);
	void Apply(glm::vec3 position);
	const glm::vec3& Min() const { return m_min; }
	const glm::vec3& Max() const { return m_max; }
	const glm::vec3& Center() const { return m_center; }
	std::string ToString();
	~BDB();

private:
	glm::vec3 m_min;
	glm::vec3 m_max;
	glm::vec3 m_center;
	
};
}
}
#endif