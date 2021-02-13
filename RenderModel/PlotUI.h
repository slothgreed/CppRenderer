#ifndef PLOT_UI_H
#define PLOT_UI_H
namespace KI
{
namespace ImGuiEx
{
class PlotLineUI
{
public:
	PlotLineUI() {};
	~PlotLineUI() {};

	void SetLabel(const std::string& value) { m_label = value; }
	void SeValue(const std::vector<float>& value) { m_value = value; }
	bool Show(std::vector<float>* value);
	bool Show(const std::vector<float>& value);

private:
	std::string m_label;
	std::vector<float> m_value;
};
}
}
#endif PLOT_UI_H
