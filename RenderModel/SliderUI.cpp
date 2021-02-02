namespace KI
{
namespace ImGuiEx
{

bool SliderIntUI::Show()
{
	if (ImGui::SliderInt(m_label.data(), &m_value, m_min, m_max)) {
		return true;
	}

	return false;
}

bool SliderFloatUI::Show()
{
	if (ImGui::SliderFloat(m_label.data(), &m_value, m_min, m_max, "%lf", 1.0f)) {
		return true;
	}

	return false;
}
}
}
