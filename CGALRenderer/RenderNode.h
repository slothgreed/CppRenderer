#ifndef RENDER_NODE_H
#define RENDER_NODE_H

class IShader;
class VertexBuffer;
class RenderNode
{
public:
	RenderNode(std::shared_ptr<IShader> shader, std::shared_ptr<VertexBuffer> buffer);
	~RenderNode();
	void Draw();
	void ShowProperty();
	void SetBDB(BDB bdb);

private:
	std::string m_name;
	std::shared_ptr<IShader> m_pShader;
	std::shared_ptr<VertexBuffer> m_pVertexBuffer;
	BDB m_bdb;
};



#endif RENDER_NODE_H
