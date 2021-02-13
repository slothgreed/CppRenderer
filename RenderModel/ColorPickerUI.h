#ifndef COLOR_PICKER_UI_H
#define COLOR_PICKER_UI_H
namespace KI
{
namespace ImGuiEx
{
class ColorPicker3UI
{
public:
	ColorPicker3UI() {};
	~ColorPicker3UI() {};

	void SetLabel(const std::string& value) { m_label = value; }
	void SeValue(const vec3& value) { m_value = value; }
	const vec3& Value() { return m_value; }
	bool Show();
private:
	std::string m_label;
	vec3 m_value;
};

class ColorPicker4UI
{
public:
	ColorPicker4UI() {};
	~ColorPicker4UI() {};

	void SetLabel(const std::string& value) { m_label = value; }
	void SeValue(const vec4& value) { m_value = value; }
	const vec4& Value() { return m_value; }
	bool Show();
private:
	std::string m_label;
	vec4 m_value;
};
}
}
#endif COLOR_PICKER_UI_H