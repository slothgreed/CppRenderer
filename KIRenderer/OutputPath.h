#ifndef OUTPUT_PATH_H
#define	OUTPUT_PATH_H

namespace KI
{
namespace Renderer
{

class DLL_EXPORT OutputPath : public IRenderPath
{
public:
	OutputPath();
	~OutputPath();

	virtual void Initialize(int width, int height) override;
	virtual void Resize(int width, int height) override;
	void SetTexture(shared_ptr<Texture> pTexture);
	void Draw(shared_ptr<IRenderTarget> pRenderTarget, shared_ptr<RenderData> pRenderData);
private:
	shared_ptr<BasicShading> m_pBasicShading;
	shared_ptr<IShader> m_pBasicShader;
};

}
}

#endif	OUTPUT_PATH_H
