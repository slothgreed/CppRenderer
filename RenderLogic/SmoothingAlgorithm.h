#ifndef SMOOTHING_ALGORITHM_H
#define SMOOTHING_ALGORITHM_H

namespace KI
{
namespace Logic
{
class SmoothingAlgorithm
{
public:
	SmoothingAlgorithm(HalfEdgeDS* halfEdgeDS);
	~SmoothingAlgorithm();

	virtual bool Execute();
private:
	HalfEdgeDS* m_halfEdgeDS;
};


}
}


#endif SMOOTHING_ALGORITHM_H