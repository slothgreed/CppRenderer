namespace KI
{
namespace Gfx
{

void IShaderCode::Load(string& code)
{
	FileUtility::Load(m_filePath, code);
}

}
}