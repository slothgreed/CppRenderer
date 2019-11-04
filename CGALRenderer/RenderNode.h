#ifndef RENDER_NODE_H
#define RENDER_NODE_H

class Shader;
class VertexBuffer;
class RenderNode
{
public:
	RenderNode(std::shared_ptr<Shader> shader, std::shared_ptr<VertexBuffer> buffer);
	~RenderNode();
	void Draw();
private:
	std::shared_ptr<Shader> m_pShader;
	std::shared_ptr<VertexBuffer> m_pVertexBuffer;
};



#endif RENDER_NODE_H
