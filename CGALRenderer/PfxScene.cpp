namespace KI
{
void PfxScene::Initialize()
{
	m_pScene = make_shared<Scene>();
	m_pScene->Initialize();
	auto pCamera = make_shared<OrthoCamera>();
	pCamera->LookAt(vec3(0, 0, 1), vec3(0), vec3(0, 1, 0));
	pCamera->Ortho(-1, 1, -1, 1, -1, 1);
	m_pScene->SetCamera(pCamera);

	auto pGrayScale = make_shared<GrayScaleEffect>();
	pGrayScale->Initialize(640, 480);

	auto pTexture = make_shared<Texture>();
	pTexture->Generate();
	TextureData textureData;
	TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\earth2048.png",textureData);
	pTexture->Begin();
	pTexture->Set(textureData);
	pTexture->End();

	pGrayScale->SetTexture(pTexture);

	m_pPfxRenderer = make_shared<PfxRenderer>();
	m_pPfxRenderer->AddPostEffect(pGrayScale);

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);

	m_pOutputTexture = pGrayScale->RenderTexture();
	m_pOutputPlane = make_shared<PfxPlane>(
		make_shared<OutputShading>(m_pOutputTexture));

}

void PfxScene::Invoke()
{
	
	m_pPfxRenderer->Draw();

	m_pBackTarget->Begin();
	m_pBackTarget->Clear();

	m_pScene->Bind(); 
	m_pOutputPlane->Draw();
	m_pScene->UnBind();
	m_pBackTarget->End();
}

void PfxScene::PreviewPfx()
{

}

void PfxScene::NextPfx()
{

}

void PfxScene::ProcessMouseEvent(const MouseInput& input)
{
	if (input.Event() == KI_MOUSE_EVENT::MOUSE_EVENT_DOWN)
	{
		if (input.Press() == KI_MOUSE_BUTTON::MOUSE_BUTTON_RIGHT)
		{
			PreviewPfx();
		}
		else if(input.Press() == KI_MOUSE_BUTTON::MOUSE_BUTTON_LEFT)
		{
			NextPfx();
		}
	}
}

void PfxScene::WindowResize(int width, int height)
{
	m_pPfxRenderer->Resize(width, height);
}


}