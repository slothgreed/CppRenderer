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