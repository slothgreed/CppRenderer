#ifndef CHECKBOX_UI_H
#define CHECKBOX_UI_H
namespace KI
{
namespace ImGuiEx
{
class CheckBoxUI
{
public:
	CheckBoxUI() {};
	~CheckBoxUI() {};

	void SetLabel(const std::string& value) { m_label = value; }
	void SeValue(bool value) { m_value = value; }
	bool Value() { return m_value; }
	bool Show();
private:
	std::string m_label;
	bool m_value;
};
}
}
#endif CHECKBOX_UI_H
