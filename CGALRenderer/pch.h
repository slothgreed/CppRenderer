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

#define DLL_EXPORT  //__declspec(dllimport)

#include<memory>
#include<string>
#include <iostream>
#include <vector>
#include<iostream>
#include<fstream>
#include <stack>

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "ImGui/imgui.h"
#include "ImGui/examples/imgui_impl_glfw.h"
#include "ImGui/examples/imgui_impl_opengl3.h"

using namespace std;
using namespace glm;

// Foundation
#include "../KIFoundation/pch.h"
using namespace KI::Foundation;

#include "../KIGfx/pch.h"
using namespace KI::Gfx;

#include "../KIRenderer/pch.h"
using namespace KI::Renderer;

#include "../KITopology/pch.h"
using namespace KI::Topology;

#include "../KIAlgorithm/pch.h"
using namespace KI::Algorithm;

#include "../KIAsset/pch.h"
using namespace KI::Asset;

// model (mvc)
#include "BDBProperty.h"
#include "NormalProperty.h"
#include "HalfEdgeProperty.h"
#include "PrimitiveNode.h"
#include "PolygonModelNode.h"
#include "HalfEdgeDSNode.h"
#include "ManipulatorNode.h"

// application
#include "IWorkspace.h"
#include "PfxScene.h"
#include "PrimitiveScene.h"
#include "BunnyScene.h"
#include "Workspace.h"
#include "VoronoiScene.h"
#include "CGALRenderer.h"
#include "Project.h"
#include "SpecialUtility.h"

// logic
#include "CameraController.h"
#include "SubdivisionCommand.h"
#include "PickCommand.h"
#include "VoxelCommand.h"
#include "LogicEventArgs.h"

template<class T, class U>
weak_ptr<T>
static_pointer_cast(std::weak_ptr<U> const& r)
{
	return static_pointer_cast<T>(shared_ptr<U>(r));
}


#endif //PCH_H
