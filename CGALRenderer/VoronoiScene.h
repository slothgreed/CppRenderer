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
	void GenerateVoronoiDiagram();
	void GenerateVoronoiPoint(vector<vec3>& position, int size);
	void GenerateVoronoiCone(const vector<vec3>& pointPosition, vector<vec3>& position, vector<vec3>& color, vector<mat4x4>& matrix, vector<int>& index);

private:
	shared_ptr<Scene> m_pScene;
	shared_ptr<PrimitiveNode> m_pConeNode;
	shared_ptr<PrimitiveNode> m_pPointNode;
	shared_ptr<IRenderTarget> m_pBackTarget;

};
}

#endif // VORONOI_SCENE_H