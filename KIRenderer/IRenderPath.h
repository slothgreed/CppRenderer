#ifndef IRENDER_PATH_H
#define	IRENDER_PATH_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT IRenderPath
{
public:
	IRenderPath() {};
	virtual ~IRenderPath() {};

	virtual void Initialize(int width, int height) = 0;
	virtual void Resize(int width, int height) = 0;
private:

};

}
}

#endif IRENDER_PATH_H