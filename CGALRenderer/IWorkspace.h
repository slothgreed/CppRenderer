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

	shared_ptr<Camera> MainCamera() { return m_pCamera; }
protected :
	shared_ptr<Camera> m_pCamera;
public:
	virtual void Initialize(Project* m_pProejct) = 0;
	virtual void Invoke() = 0;
	virtual void ShowProperty() = 0;

};

}

#endif // CGAL_RENDERER_INITIALIZER_H