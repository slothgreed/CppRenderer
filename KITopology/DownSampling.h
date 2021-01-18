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
		int Index() { return m_Index; }
		float Area() { return m_Area; }
		vec3 Position() { return m_Position; }
		vec3 Normal() { return m_Normal; }

	private:
		int m_Index;
		float m_Area;
		vec3 m_Position;
		vec3 m_Normal;
	};

	// ñÿç\ë¢ÇÃê[Ç≥ñàÇÃèÓïÒÇéùÇ¬
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
		//         Å^Å@Å_
		//	2:	  b      c
		//	    Å^ Å_   Å^Å_
		//	3: d     e f    g
		//	
		int m_UpperNum;
		int m_LowerNum;
		// cube.obj;
		// to_upper : (0,1) (2,6) (3,7) (4,5)
		// to_lower : 0, 0, 1, 2, 3, 3, 1, 2
		// index    : 0, 1, 2, 3, 4, 5, 6, 7
		std::vector<ivec2> m_toUpper;  // Resolution 2 ÇÃÇ∆Ç´ a
		std::vector<int> m_toLower;	  // Resolution 2 ÇÃÇ∆Ç´ (d,e)(f,g)
		std::vector<SampleData> m_pSampleData;
		shared_ptr<AdjancyMatrix> m_pMatrix;
	};

	DownSampling(HalfEdgeDS* pHalfEdgeDS, int maxLevel);
	~DownSampling() {};
	void Generate();
	shared_ptr<DownSampling::Resolution> GetResolution(int level);
	int GetResolutionNum() { return (int)m_pResolution.size(); }
	void GetCluster(int level, std::vector<int>& index);	// original í∏ì_ÇÃèáî‘
private:
	void InitialResolution(shared_ptr<DownSampling::Resolution> pResolution, HalfEdgeDS* pHalfEdgeDS);
	void GetClusterRecursive(int level, int targetLevel, int upper, int clusterIndex, std::vector<int>& index);
	void CreateResolution(int level, shared_ptr<DownSampling::Resolution> pOrgResolution, shared_ptr<DownSampling::Resolution> pResolution);
	HalfEdgeDS* m_pHalfEdgeDS;
	vector<shared_ptr<DownSampling::Resolution>> m_pResolution;	// indexÇ™ëÂÇ´Ç¢ÇŸÇ«çrÇ¢
	int m_maxLevel;
	
};

}
}

#endif // !DOWN_SAMPLING_HPP
