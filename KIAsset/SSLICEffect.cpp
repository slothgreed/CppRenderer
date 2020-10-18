#include "../KIGfx/BlendState.h"
namespace KI
{
namespace Asset
{	
SSLICEffect::SSLICEffect()
{
}

SSLICEffect::~SSLICEffect()
{
}

void SSLICEffect::Initialize(int width, int height)
{
	//if (width != height)
	//{
	//	assert(0);
	//	width = height;
	//}
	TextureData textureData;
	TextureGenerator::RandomTexture(64, 15, textureData);
	m_pNoizeTexture = make_shared<Texture>();
	m_pNoizeTexture->Generate();
	m_pNoizeTexture->Begin();
	m_pNoizeTexture->Set(textureData);
	m_pNoizeTexture->End();

	m_pRenderTarget = make_shared<RenderTarget>();
	m_pRenderTarget->Initialize(1, width, height);
	m_pRenderTarget->SetClearColor(vec4(0));

	m_pPlaneData = make_shared<PfxPlane>();
	m_pPlaneData->SetTexture(m_pNoizeTexture);

	TextureData blendTexture;
	blendTexture.width = width;
	blendTexture.height = height;
	//TextureGenerator::FillTexture(vec4(255), blendTexture);

	m_pBlendTexture = make_shared<Texture>();
	m_pBlendTexture->Generate();
	m_pBlendTexture->Begin();
	m_pBlendTexture->Set(blendTexture);
	m_pBlendTexture->End();

	//m_pBasicShading->SetTexture(m_pNoizeTexture);
	
	m_BlendState.Enable(true);
	m_BlendState.BlendFunc(BLEND_FACTOR_SRC_ALPHA, BLEND_FACTOR_ONE_MINUS_SRC_ALPHA);
}

shared_ptr<Texture> SSLICEffect::RenderTexture(int index)
{
	if (index == 0)
	{
		return m_pRenderTarget->ColorTexture(FRAMEBUFFER_COLOR_ATTACHMENT0);
	}

	if (index == 1)
	{
		return m_pNoizeTexture;
	}

	if (index == 2)
	{
		return m_pBlendTexture;
	}

	return nullptr;
}
void SSLICEffect::SetModelNode(shared_ptr<IModelNode> pModelNode)
{
	m_pModelNode = pModelNode;
	m_pBasicShading = make_shared<BasicShading>(m_pBlendTexture);

	auto pBuildInfo = make_shared<IShaderBuildInfo>();
	pBuildInfo->SetVertexBuffer(m_pModelNode->GetRenderData(0)->GetVertexBuffer());
	pBuildInfo->SetShaderChunk(m_pBasicShading);
	m_pBasicShader = ShaderManager::Instance()->FindOrNew(pBuildInfo);
}

void SSLICEffect::Draw(shared_ptr<UniformStruct> pUniform)
{
	m_pRenderTarget->Begin();
	m_pRenderTarget->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_pModelNode->FixedShaderDraw(m_pBasicShader, m_pBasicShading, pUniform);

	m_BlendState.Bind();
	m_pPlaneData->Draw();
	m_BlendState.UnBind();

	m_pRenderTarget->CopyColorBuffer(FRAMEBUFFER_COLOR_ATTACHMENT0, m_pBlendTexture.get());
	
	m_pRenderTarget->End();
}

void SSLICEffect::Resize(int width, int height)
{
	m_pRenderTarget->Resize(width, height);
	m_pBlendTexture->Resize(width, height);
}

}
}