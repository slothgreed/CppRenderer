#ifndef BDB_UTILITY_H
#define BDB_UTILITY_H
namespace KI
{
namespace Foundation
{
class DLL_EXPORT BDBUtility
{
public:
	BDBUtility() {};
	~BDBUtility() {};
	static mat4x4 GetModelMatrixFromMin(const BDB& bdb);
};
}
}
#endif BVH_H