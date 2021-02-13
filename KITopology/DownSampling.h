#ifndef DOWN_SAMPLING_HPP
#define DOWN_SAMPLING_HPP

namespace KI
{
namespace Topology
{

class DLL_EXPORT DownSampling
{
public:

	class SampleData
	{
	public:
		SampleData() {};
		SampleData(int positionNum);
		~SampleData();
		void Set(int index, const vec3& position, const vec3& normal, float area);
		void SetTangent(const vec3& tangent) { m_tangent = tangent; }
		int Index() { return m_index; }
		float Area() { return m_area; }
		vec3 Position() { return m_position; }
		vec3 Normal() { return m_normal; }
		vec3 Tangent() { return m_tangent; }
	private:
		int m_index;
		float m_area;
		vec3 m_position;
		vec3 m_normal;
		vec3 m_tangent;
	};

	// –Ø\‘¢‚Ì[‚³–ˆ‚Ìî•ñ‚ğ‚Â
	class Resolution
	{
	public:
		Resolution();
		~Resolution();
		SampleData* GetData(int index);
		void SetToUpper(int index, int value1, int value2);
		ivec2  GetToUpper(int index);
		int  GetToUpper(int index1, int index2);

		void SetToLower(int index, int value);
		int GetToLower(int index);
		int GetClusterNum() { return m_UpperNum; }
		int GetBranchNum() { return 2; }
		void SetAdjancyMatrix(shared_ptr<AdjancyMatrix> pMatrix) { m_pMatrix = pMatrix; };
		shared_ptr<AdjancyMatrix> GetAdjancyMatrix() { return m_pMatrix; }
		void NewData(int positionNum, int originalPosNum);
		void FreeData();
	private:
		//	1:	     a
		//         ^@_
		//	2:	  b      c
		//	    ^ _   ^_
		//	3: d     e f    g
		//	
		int m_UpperNum;
		int m_LowerNum;
		// cube.obj;
		// to_upper : (0,1) (2,6) (3,7) (4,5)
		// to_lower : 0, 0, 1, 2, 3, 3, 1, 2
		// index    : 0, 1, 2, 3, 4, 5, 6, 7
		std::vector<ivec2> m_toUpper;  // Resolution 2 ‚Ì‚Æ‚« a = To Detail ×‚©‚¢•û‚Ö‚ÌƒCƒ“ƒfƒbƒNƒX
		std::vector<int> m_toLower;	  // Resolution 2 ‚Ì‚Æ‚« r‚¢•û‚Ö‚ÌƒCƒ“ƒfƒbƒNƒX
		std::vector<SampleData> m_pSampleData;
		shared_ptr<AdjancyMatrix> m_pMatrix;
	};

	DownSampling(HalfEdgeDS* pHalfEdgeDS);
	~DownSampling() {};
	void Generate();
	shared_ptr<DownSampling::Resolution> GetResolution(int level);
	int GetResolutionNum() { return (int)m_pResolution.size(); }
	void GetCluster(int level, std::vector<int>& index);	// original ’¸“_‚Ì‡”Ô
private:
	void InitialResolution(shared_ptr<DownSampling::Resolution> pResolution, HalfEdgeDS* pHalfEdgeDS);
	void GetClusterRecursive(int level, int upper, int clusterIndex, std::vector<int>& index);
	void CreateResolution(int level, shared_ptr<DownSampling::Resolution> pOrgResolution, shared_ptr<DownSampling::Resolution> pResolution);
	HalfEdgeDS* m_pHalfEdgeDS;
	vector<shared_ptr<DownSampling::Resolution>> m_pResolution;	// index‚ª‘å‚«‚¢‚Ù‚Çr‚¢
	
};

}
}

#endif // !DOWN_SAMPLING_HPP
