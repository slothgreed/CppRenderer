#ifndef CGAL_MODEL_H
#define CGAL_MODEL_H
class CGALModel
{
public:
	CGALModel();
	~CGALModel();

	virtual void Load(const std::string& filePath) = 0;
private:

};

#endif CGAL_MODEL_H