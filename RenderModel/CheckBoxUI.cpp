namespace KI
{
namespace ImGuiEx
{

bool CheckBoxUI::Show()
{
	if (ImGui::Checkbox(m_label.data(), &m_value)) {
		return true;
	}

	return false;
}
}
}