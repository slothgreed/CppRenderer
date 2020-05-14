#ifndef SHADER_UTILITY_H
#define SHADER_UTILITY_H
namespace KI
{
namespace Gfx
{
class DLL_EXPORT ShaderUtility
{
public:
	ShaderUtility();
	~ShaderUtility();
	
	static GLuint Compile(const string& code, GLuint shaderType);
	static GLuint Link(GLuint vertexId, GLuint tcsId, GLuint tesId, GLuint geomId, GLuint fragId);
	
	static void Load(string filePath, string& shaderCode);

	// 組み込み識別文字列がある場合、その位置に文字列を組み込む、ない場合組み込み識別文字列を削除する。
	// [in, out]	: code;
	// embeddedCode : 組み込む文字列
	// embeddedIdentifier : 組み込む位置の文字列
	static void EmbeddedCode(string& code, const string& embeddedCode, const string& embeddedIdentifier);

private:
	// シェーダコードを展開する.
	static void ExpandShaderCode(const string& filePath, string& shaderCode);

	static string m_shaderDirectory;

};
}
}

#endif SHADER_UTILITY_H
