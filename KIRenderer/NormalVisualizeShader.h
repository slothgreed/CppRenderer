#ifndef KI_NORMAL_VISUALIZE_SHADER_H
#define KI_NORMAL_VISUALIZE_SHADER_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT NormalVisualizeShader : public IShader
{
public:
	NormalVisualizeShader();
	~NormalVisualizeShader();
	virtual SHADER_TYPE Type() override { return SHADER_TYPE::SHADER_TYPE_NORMALVISUALIZE; }
private:

};


}
}

#endif