#ifndef MODEL_NODE_H
#define MODEL_NODE_H

class IShader;
class VertexBuffer;
class IModelProperty;
class ModelNode
{
public:
	ModelNode(std::shared_ptr<IShader> shader, std::shared_ptr<VertexBuffer> buffer);
	~ModelNode();
	void Draw();
	void SetBDB(BDB bdb);
	void ShowProperty();
private:
	std::string m_name;
	std::shared_ptr<IShader> m_pShader;
	std::shared_ptr<VertexBuffer> m_pVertexBuffer;
	std::vector<std::shared_ptr<IModelProperty>> m_pProperty;
	BDB m_bdb;
	bool m_showBDB;
};



#endif MODEL_NODE_H
