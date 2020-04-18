#ifndef IPICKABLE_H
#define IPICKABLE_H

namespace KI
{
namespace Renderer
{
class RenderData;
class DLL_EXPORT PickInfo
{
public:
	PickInfo() {};
	~PickInfo() {};
	void Set(shared_ptr<RenderData> pRenderData, const vector<vec3>& pPickInfo);
	shared_ptr<RenderData> GetRenderData() { return m_pRenderData; };
private:
	vector<vec3> m_pPickInfo;
	shared_ptr<RenderData> m_pRenderData;
};

class DLL_EXPORT IPickable
{
public:
	IPickable() {};
	~IPickable() {};
	
	virtual void CalculatePickID(int startIndex, int& nextStartIndex) = 0;
	virtual void PickDraw() = 0;
	shared_ptr<RenderData> GetPickRenderData(int key);

protected:
	vec3 IndexToColor(int index);
	virtual void CalculateID(GLuint primitiveType, int indexNum, int startIndex, int& nextStartIndex, vector<vec3>& ids);
	void BuildPickData(int key, shared_ptr<RenderData> pRenderData, const vector<vec3>& ids);
private:
	map<int, PickInfo> m_pPickInfo; // key = identifier, value = id;
};

}
}

#endif