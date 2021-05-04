#ifndef HUD_TEXT_H
#define HUD_TEXT_H

namespace KI
{
namespace Asset
{

class DLL_EXPORT HUDTextArgs
{
public:
	HUDTextArgs() {};
	HUDTextArgs(const std::string& text, int left, int top)
		:m_text(text),
		m_left(left),
		m_top(top) {};
	~HUDTextArgs() {};
	std::string m_text;
	int m_left;
	int m_top;
};

class DLL_EXPORT HUDText : public IHUD
{
public:
	HUDText() {};
	HUDText(const HUDTextArgs& args);
	~HUDText() {};
	void Build(const HUDTextArgs& args);
	shared_ptr<Texture> GetTexture();
private:
	std::string m_text;
};


}
}

#endif HUD_TEXT_H