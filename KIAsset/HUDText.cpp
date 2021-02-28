
namespace KI
{
namespace Asset
{

HUDText::HUDText(const HUDTextArgs& args)
{
	Build(args);
}

void HUDText::Build(const HUDTextArgs& args)
{
	SetWindowPosition(args.m_top, args.m_left);
	TextTextureGenerator::Instance().Generate(args.m_text, &m_position, &m_index, &m_texcoord);
}

shared_ptr<Texture> HUDText::GetTexture()
{
	return TextTextureGenerator::Instance().GetTexture();
}
}
}