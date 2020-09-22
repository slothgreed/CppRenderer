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

	auto pTexture = make_shared<Texture>();
	pTexture->Generate();
	TextureData textureData;
	TextureGenerator::Load("E:\\cgModel\\texture\\SkyBox\\earth2048.png",textureData);
	pTexture->Begin();
	pTexture->Set(textureData);
	pTexture->End();


	m_pPfxRenderer = make_shared<PfxRenderer>();

	// gray scale
	{
		auto pGrayScale = make_shared<GrayScaleEffect>();
		pGrayScale->Initialize(640, 480);
		pGrayScale->SetTexture(pTexture);
		m_pPfxRenderer->AddPostEffect(pGrayScale);
	}

	// sslic effect
	{
		auto pSSLICEffect = make_shared<SSLICEffect>();
		pSSLICEffect->Initialize(480, 480);
		auto pModel = make_shared<RenderData>();
		SpecialUtility::LoadVectorFieldSphere(pModel.get());

		auto pModelNode = make_shared<PrimitiveNode>(pModel);
		TextureData data;
		TextureGenerator::RandomTexture(8, 15, data);
		auto texture = make_shared<Texture>();
		texture->Generate();
		texture->Begin();
		texture->Set(data);
		texture->End();
		auto pBasicShading = make_shared<BasicShading>(texture);
		pModel->SetShading(pBasicShading);
		m_pScene->AddModelNode(pModelNode);

		pSSLICEffect->SetModelNode(pModelNode);
		m_pPfxRenderer->AddPostEffect(pSSLICEffect);
	}

	m_pBackTarget = make_shared<SymbolicRenderTarget>(GL_BACK);
	m_pOutputPlane = make_shared<PfxPlane>();

	m_CurrentIndex = 0;
	SetOutputTexture(m_CurrentIndex);
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
	if (SetOutputTexture(m_CurrentIndex - 1))
	{
		m_CurrentIndex--;
	}
}

void PfxScene::NextPfx()
{
	if (SetOutputTexture(m_CurrentIndex + 1))
	{
		m_CurrentIndex++;
	}
}

bool PfxScene::SetOutputTexture(int index)
{
	int counter = 0;
	for (int i = 0; i < m_pPfxRenderer->PostEffectNum(); i++)
	{
		auto pPfx = m_pPfxRenderer->FindPostEffectByIndex(index);
		if (pPfx == NULL)
		{
			return false;
		}

		for (int j = 0; j < pPfx->RenderTextureNum(); j++)
		{
			if (counter == index)
			{
				m_pOutputPlane->SetTexture(pPfx->RenderTexture(counter));
				break;
			}

			counter++;
		}
	}

	return true;
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
