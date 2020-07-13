// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef KI_SHADER_LIB_PCH_H
#define KI_SHADER_LIB_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

// プリコンパイルするヘッダーをここに追加します
#include<memory>
#include<string>
#include<algorithm>
#include<vector>
#include<iostream>
#include<fstream>
#include<stack>

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace std;
using namespace glm;

#include "../KIFoundation/pch.h"
using namespace KI::Foundation;

#include "../KIGfx/pch.h"
using namespace KI::Gfx;

#include "ShaderLibTypes.h"
#include "Define.h"

#include "IShading.h"

#include "UniformMaterial.h"
#include "UniformModel.h"
#include "UniformScene.h"
#include "UniformLight.h"
#include "UniformStruct.h"
#include "UniformBuilder.h"

#include "ShaderCommon.h"
#include "ShaderStruct.h"
#include "DefaultVBOCode.h"
#include "DefaultVertexCode.h"
#include "DefaultVertexBuffer.h"

#include "PostProcessCode.h"
#include "SimpleShaderCode.h"

#include "OutputShading.h"
#include "CompositShading.h"
#include "SSLICShading.h"
#include "VertexShading.h"
#include "BasicShading.h"
#include "LambertShading.h"
#include "NormalVisualizeShading.h"
#include "OutputShading.h"
#include "GrayScaleShading.h"
#include "BezierLineShading.h"
#include "PhongShading.h"
#endif //KI_SHADER_LIB_PCH_H
