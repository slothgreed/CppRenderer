#ifndef CGAL_RENDERER_INITIALIZER_H
#define	CGAL_RENDERER_INITIALIZER_H

namespace KI
{
class Project;
class IWorkspace
{
public:
	IWorkspace() {};
	virtual ~IWorkspace() {};

public:
	virtual void Initialize(Project* m_pProejct) = 0;
	virtual void Invoke() = 0;
	virtual void ShowProperty() = 0;
	virtual void ProcessMouseEvent(const MouseInput& input) = 0;

};

}

#endif // CGAL_RENDERER_INITIALIZER_H