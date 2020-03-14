#ifndef VORONOI_SCENE_H
#define	VORONOI_SCENE_H

namespace KI
{
class VoronoiScene : public IWorkspace
{
public:
	virtual void Initialize(Project* pProject) override;
	virtual void Invoke() override;
	virtual void ProcessMouseEvent(const MouseInput& input)override;

private:
	shared_ptr<UniformScene> m_pUnifromScene;
	shared_ptr<ICamera> m_pCamera;
	vector<shared_ptr<IModelNode>> m_pModelNode;
	shared_ptr<PrimitiveNode> m_pConeNode;
	shared_ptr<PrimitiveNode> m_pPointNode;
	shared_ptr<IRenderTarget> m_pBackTarget;

};
}

#endif // VORONOI_SCENE_H