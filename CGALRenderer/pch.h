// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します

#ifndef PCH_H
#define PCH_H

// TODO: ここでプリコンパイルするヘッダーを追加します

#include<memory>
#include<string>
#include <iostream>
#include <vector>
#include<iostream>
#include<fstream>

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

// system
#include "SystemTypes.h"
#include "Logger.h"
#include "FileIO.h"
#include "Mouse.h"
#include "MouseInput.h"
#include "WindowEvent.h"

// utility
#include "MathHelper.h"
#include "ShaderUtility.h"
#include "ModelGenerator.h"

// opengl
#include "Shader.h"
#include "ShaderData.h"
#include "ShaderScene.h"
#include "VertexBuffer.h"
#include "Viewport.h"

// asset
#include "Camera.h"
#include "RenderNode.h"
#include "CGALModel.h"
#include "CGALPolyhedron.h"

// logic
#include "IController.h"
#include "IControllerArgs.h"
#include "CameraController.h"

// application
#include "CGALRenderer.h"
#include "Project.h"
#include "Workspace.h"


using namespace std;
using namespace glm;

#define USE_VAR(x) (void)x;
#define RELEASE_INSTANCE(x) if(x != NULL) { delete x; x = NULL;}


#endif //PCH_H
