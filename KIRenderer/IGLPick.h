#ifndef IGLPICK_H
#define IGLPICK_H

namespace KI
{
namespace Renderer
{
class RenderData;

// Selection Buffer ‚ð—˜—p‚µ‚½Picking
class DLL_EXPORT GLPickInfo
{
public:
	GLPickInfo() {};
	~GLPickInfo() {};
	void Set(shared_ptr<RenderData> pRenderData, const vector<vec3>& pPickInfo) { m_pRenderData = pRenderData; m_pPickInfo = pPickInfo; };
	shared_ptr<RenderData> GetRenderData() { return m_pRenderData; };
private:
	shared_ptr<RenderData> m_pRenderData;
	vector<vec3> m_pPickInfo;
};

class DLL_EXPORT IGLPick
{
public:
	IGLPick() {};
	~IGLPick() {};
	
	virtual void CalculatePickID(int startIndex, int& nextStartIndex) = 0;
	virtual void PickDraw() = 0;
	shared_ptr<RenderData> GetPickRenderData(int key);

protected:
	vec3 IndexToColor(int index);
	virtual void CalculateID(GLuint primitiveType, int indexNum, int startIndex, int& nextStartIndex, vector<vec3>& ids);
	void BuildPickData(int key, shared_ptr<RenderData> pRenderData, const vector<vec3>& ids);
private:
	map<int, GLPickInfo> m_pPickInfo; // key = identifier, value = id;
};

}
}

#endif