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
	//ImGui::Begin("Text", &open, 
	//	ImGuiWindowFlags_::ImGuiWindowFlags_NoResize|
	//	ImGuiWindowFlags_::ImGuiWindowFlags_NoTitleBar|
	//	ImGuiWindowFlags_::ImGuiWindowFlags_NoScrollbar);
	//ImGui::SetWindowPos(ImVec2(m_windowPos.x, m_windowPos.y));
	//ImGui::SetWindowSize(ImVec2(600, 600));
	//ImGui::Text(Value().data());
	//ImGui::End();
    ImVec2 bmin = ImVec2(100, 100); //テキストの描画位置. ImGui::GetCursorScreenPos() などで取得

    ImVec2 text_size = ImGui::CalcTextSize("value2");

    ImVec2 fill_bmin = ImVec2(bmin.x - 4, bmin.y - 4);
    ImVec2 fill_bmax =
        ImVec2(bmin.x + text_size.x + 4, bmin.y + text_size.y + 4);

    // Draw quad for background color
    ImGui::GetWindowDrawList()->AddRectFilled(
        fill_bmin, fill_bmax,
        ImGui::GetColorU32(ImVec4(0.2f, 0.2f, 0.2f, 0.4f * 1.0)),
        /* rounding */ 4.0f);


    ImGui::SetCursorScreenPos(bmin);

    ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0), "%s", "value2");

}
}
}