namespace ImGuiEx
{
template<typename T>
struct SliderUI
{
	std::string label;
	T value;
	T min;
	T max;
};

template struct SliderUI<int>;
template struct SliderUI<float>;


struct CheckBoxUI
{
	std::string label;
	bool value;
};
}