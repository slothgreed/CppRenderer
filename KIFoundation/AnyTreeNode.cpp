namespace KI
{
namespace Foundation
{

AnyTreeNode::AnyTreeNode()
{
}

AnyTreeNode::~AnyTreeNode()
{
	FreeData();
}

void AnyTreeNode::FreeData()
{
	RELEASE_INSTANCE(m_pData);
}

void AnyTreeNode::NewData(int childNum, void* pData)
{
	m_ChildNum = childNum;
	m_pChild.resize(m_ChildNum);
	m_pData = pData;
}

AnyTreeNode* AnyTreeNode::GetChild(int index1)
{
	assert(m_ChildNum > index1);
	return m_pChild[index1];
}
void AnyTreeNode::SetChild(int index1, AnyTreeNode* value)
{
	assert(m_ChildNum > index1);
	m_pChild[index1] = value;
}
void AnyTreeNode::SetParent(AnyTreeNode* value)
{
	m_pParent = value;
}

AnyTreeNode* AnyTreeNode::GetParent()
{
	return m_pParent;
}

void* AnyTreeNode::GetData()
{
	return m_pData;
}
}
}