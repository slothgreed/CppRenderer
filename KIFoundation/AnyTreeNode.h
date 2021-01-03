#ifndef DOWNSAMPLE_LAYER_H
#define DOWNSAMPLE_LAYER_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT AnyTreeNode
{
public:

	AnyTreeNode();
	~AnyTreeNode();
	void* GetData();
	void SetChild(int index1, AnyTreeNode* pLayer);
	AnyTreeNode*  GetChild(int index1);
	void SetParent(AnyTreeNode* value);
	AnyTreeNode* GetParent();
	int GetChildNum() { return m_ChildNum; }
	void NewData(int childNum, void* pData);
	void FreeData();
private:
	std::vector<AnyTreeNode*> m_pChild;	
	AnyTreeNode* m_pParent;				
	int m_ChildNum;
	void* m_pData;

};
}
}
#endif DOWNSAMPLE_LAYER_H
