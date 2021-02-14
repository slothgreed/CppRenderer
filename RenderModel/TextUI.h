#ifndef TEXT_UI_H
#define TEXT_UI_H
namespace KI
{
namespace ImGuiEx
{
class TextUI
{
public:
	TextUI() {};
	~TextUI() {};
	virtual void SetValue(const std::string& text) { m_text = text; };
	const std::string& Value() { return m_text; }
	virtual void ShowUI();
private:
	std::string m_text;
};

class NoWindowTextUI : public TextUI
{
public:
	NoWindowTextUI() {};
	~NoWindowTextUI() {};
	void SetPosition(const vec2 pos) { m_windowPos = pos; };
	virtual void ShowUI() override;
private:
	vec2 m_windowPos;
};

}
}
#endif TEXT_UI_H
