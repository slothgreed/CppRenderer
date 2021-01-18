// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef RENDER_LOGIC_PCH_H
#define RENDER_LOGIC_PCH_H


#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

// プリコンパイルするヘッダーをここに追加します

// Foundation
#include "../KIFoundation/pch.h"
using namespace KI::Foundation;

#include "../KIGfx/pch.h"
using namespace KI::Gfx;

#include "../KIShaderLib/pch.h"
using namespace KI::ShaderLib;

#include "../KIRenderer/pch.h"
using namespace KI::Renderer;

#include "../KITopology/pch.h"
using namespace KI::Topology;

#include "../KIAlgorithm/pch.h"
using namespace KI::Algorithm;

#include "../KIAsset/pch.h"
using namespace KI::Asset;

#include "../RenderModel/pch.h"
using namespace KI::RenderModel;

// logic

// controller
#include "CameraController.h"

// event
#include "LogicEventArgs.h"

// geometry command
#include "VoxelCommand.h"
#include "SubdivisionCommand.h"
#include "SmoothingCommand.h"
#include "SmoothingAlgorithm.h"


// graphics command
#include "SaveImageCommand.h"
#include "PickCommand.h"
#include "ClearPickCommand.h"


#endif //RENDER_LOGIC_PCH_H
