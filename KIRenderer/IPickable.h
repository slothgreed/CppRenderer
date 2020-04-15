#ifndef IPICKABLE_H
#define IPICKABLE_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT IPickable
{
public:
	IPickable() {};
	~IPickable() {};
	
	virtual void SetPickID(int startIndex, int& endIndex) = 0;
private:
};

}
}

#endif