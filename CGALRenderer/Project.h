#ifndef PROJECT_H
#define PROJECT_H
namespace KI
{
class Project
{
public:
	Project();
	~Project();

	void Initialize();

	const std::string& ProjectDir() const { return m_projectDir; }
private:
	std::string m_projectDir;
};
}
#endif // !PROJECT_H

