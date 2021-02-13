namespace KI
{
namespace ImGuiEx
{
bool PlotLineUI::Show(std::vector<float>* value)
{
	ImGui::PlotLines(m_label.data(), value->data(), value->size());
	return true;
}

bool PlotLineUI::Show(const std::vector<float>& value)
{
	ImGui::PlotLines(m_label.data(), value.data(), value.size());
	return true;
}
}
}