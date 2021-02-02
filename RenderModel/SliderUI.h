#ifndef SLIDER_UI_H
#define SLIDER_UI_H
namespace KI
{
namespace ImGuiEx
{

class SliderIntUI
{
public:
	SliderIntUI() {};
	~SliderIntUI() {};

	void SetLabel(const std::string& value) { m_label = value; };
	void SetMax(int value) { m_max = value; }
	void SetMin(int value) { m_min = value; }
	void SetValue(int value) { m_value = value; }
	int Value() { return m_value; }
	bool Show();
private:
	std::string m_label;
	int m_value;
	int m_min;
	int m_max;
};

class SliderFloatUI
{
public:
	SliderFloatUI() {};
	~SliderFloatUI() {};

	void SetLabel(const std::string& value) { m_label = value; };
	void SetMax(float value) { m_max = value; }
	void SetMin(float value) { m_min = value; }
	void SetValue(float value) { m_value = value; }
	float Value() { return m_value; }
	bool Show();
private:
	std::string m_label;
	float m_value;
	float m_min;
	float m_max;
};
}
}
#endif SLIDER_UI_H
