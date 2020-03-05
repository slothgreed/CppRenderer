#ifndef GEOMETRY_PASS_H
#define	GEOMETRY_PASS_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT GeometryPass
{
public:
	GeometryPass();
	~GeometryPass();

	void Initialize(int width, int height);
	void Resize(int width, int height);
	void Draw(const vector<shared_ptr<IModelNode>>& modelNodes);
private:
	shared_ptr<RenderTarget> m_pRenderTarget;
};

}
}

#endif GEOMETRY_PASS_H