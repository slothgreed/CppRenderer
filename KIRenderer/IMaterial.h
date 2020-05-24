#ifndef IMATERIAL_H
#define IMATERIAL_H

namespace KI
{
namespace Renderer
{
class DLL_EXPORT IMaterial : public IShaderChunk
{
public:
	IMaterial() {};
	virtual ~IMaterial() {};

};

}
}

#endif
