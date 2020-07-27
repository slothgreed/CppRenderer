namespace KI
{
namespace Gfx
{
IRenderTarget::IRenderTarget()
{
	m_pClearColor = vec4(1);
	m_size = vec4(0);
}

IRenderTarget::~IRenderTarget()
{
}

void IRenderTarget::Begin()
{
	Bind();

	m_modifing = true;
}

void IRenderTarget::End()
{
	UnBind();

	m_modifing = false;
}

void IRenderTarget::Clear(GLbitfield clear)
{
	if (Modifing() == false)
	{
		assert(0);
	}

	glClearColor(m_pClearColor.r, m_pClearColor.g, m_pClearColor.b, m_pClearColor.a);
	glClear(clear);
}

bool IRenderTarget::GetPixels(ReadPixelArgs& args)
{
	m_size.x = 640;
	m_size.y = 480;
	args.width = 640;
	args.height = 480;
	if (m_size.x == 0 ||
		m_size.y == 0 ||
		m_size.x < args.width ||
		m_size.y < args.height)
	{
		assert(0);
		return false;
	}
	
	int dataSize = glEx::ColorFormatSize(args.format);

	args.pixels = new GLubyte[
		(args.width - args.x) * 
		(args.height - args.y) * 
		dataSize];

	Logger::GLError();

	glReadPixels(
		args.x,
		args.y,
		args.width,
		args.height,
		args.format,
		args.type,
		args.pixels);

	Logger::GLError();

	return true;
}

}
}