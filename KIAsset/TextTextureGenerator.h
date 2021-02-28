#ifndef TEXT_TEXTURE_GENERATOR_H
#define TEXT_TEXTURE_GENERATOR_H
namespace KI
{
namespace Asset
{
class DLL_EXPORT TextTextureGenerator
{
public:
	
	static TextTextureGenerator& Instance();
	
	TextTextureGenerator() {};
	~TextTextureGenerator() {};
	void Generate(const std::string& text, std::vector<vec3>* position, std::vector<int>* m_index, std::vector<vec2>* texcoord);
	shared_ptr<Texture> GetTexture() { return m_texture; };
private:
	struct Charactor
	{
		Charactor() {};
		Charactor(vec2 p, vec2 s, vec2 ps) : 
			m_position(p), m_size(s), m_pixelSize(ps), m_buffer(nullptr) {};
		~Charactor() { RELEASE_INSTANCE(m_buffer); }
		void BufferCopy(unsigned char* buf);
		vec2 m_position;
		vec2 m_size;
		vec2 m_pixelSize;
		unsigned char* m_buffer;
	};
	void GenerateTexture();
	bool Initialize();

	static TextTextureGenerator* m_Instance;
	bool m_Initialize;
	std::string m_textList;
	std::map<char, Charactor*> m_charactos;
	std::shared_ptr<Texture> m_texture;
};
}
}
#endif	