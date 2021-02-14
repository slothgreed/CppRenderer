#ifndef CAMERA_NODE_H
#define CAMERA_NODE_H

namespace KI
{
namespace RenderModel
{
class DLL_EXPORT CameraNode : public IRenderModelNode
{
public:
	CameraNode(shared_ptr<ICamera> pCamera);
	~CameraNode();
	void SetRenderData();
	virtual void Update(void* sender, IEventArgs* args);
	const ICamera* GetCamera() const { return m_pCamera.get(); }
private:
	shared_ptr<ICamera> m_pCamera;
	shared_ptr<DefaultVertexBuffer> m_pVertexBuffer;
};
}
}

#endif CAMERA_NODE_H