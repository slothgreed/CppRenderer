namespace KI
{
namespace ImGuiEx
{
void TextUI::ShowUI()
{
	ImGui::Text(Value().data());
}

void NoWindowTextUI::ShowUI()
{
	bool open = true;
	ImGui::Begin("Text", &open, 
		ImGuiWindowFlags_::ImGuiWindowFlags_NoResize|
		ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar
	);
	ImGui::SetWindowPos(ImVec2(m_windowPos.x, m_windowPos.y));
	ImGui::Text(Value().data());
	ImGui::End();

}
}
}