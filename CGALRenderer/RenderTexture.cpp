namespace KI
{
RenderTexture::RenderTexture()
{
}

RenderTexture::~RenderTexture()
{
}

void RenderTexture::Resize(int width, int height)
{
	Bind();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB8, GL_UNSIGNED_BYTE, (void*)0);
	UnBind();
}
}
