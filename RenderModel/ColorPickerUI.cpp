namespace KI
{
namespace ImGuiEx
{

bool ColorPicker3UI::Show()
{
	if (ImGui::ColorPicker3(m_label.data(), &m_value[0])) {
		return true;
	}

	return false;
}


bool ColorPicker4UI::Show()
{
	if (ImGui::ColorPicker4(m_label.data(), &m_value[0])) {
		return true;
	}

	return false;
}
}
}