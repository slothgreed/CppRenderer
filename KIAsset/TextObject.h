#ifndef TEXT_OBJECT_H
#define TEXT_OBJECT_H

namespace KI
{
namespace Asset
{
class DLL_EXPORT TextObjectArgs
{
public:
	TextObjectArgs(const std::string& text, vec2 position)
		:m_text(text),
		m_position(position) {};
	~TextObjectArgs() {};
	std::string m_text;
	vec2 m_position;

};

class DLL_EXPORT TextObject : public IPrimitive
{
public:
	TextObject(const TextObjectArgs& args);
	~TextObject(){};
	void Build(const TextObjectArgs& args);
private:
	std::string m_text;
};

}
}



#endif TEXT_OBJECT_H