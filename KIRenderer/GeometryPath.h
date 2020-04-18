#ifndef GEOMETRY_PATH_H
#define	GEOMETRY_PATH_H

namespace KI
{
namespace Renderer
{
	class DLL_EXPORT GeometryPath : public IGeometryPath
{
public:
	GeometryPath();
	~GeometryPath();

	void Initialize(int width, int height);
	void Resize(int width, int height);
	void Draw(const vector<shared_ptr<IModelNode>>& modelNodes);
private:
	shared_ptr<RenderTarget> m_pRenderTarget;
};

}
}

#endif GEOMETRY_PATH_H