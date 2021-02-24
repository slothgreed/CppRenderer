#include <ft2build.h>
#include FT_FREETYPE_H  
namespace KI
{
namespace Asset
{

TextObject::TextObject(const TextObjectArgs& args)
{
	Build(args);
}

void TextObject::Build(const TextObjectArgs& args)
{
	TextTextureGenerator::Instance().Generate(args.m_text, &m_position, &m_index, &m_texcoord);


}
}
}