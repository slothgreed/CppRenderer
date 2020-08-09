// pch.h: プリコンパイル済みヘッダー ファイルです。
// 次のファイルは、その後のビルドのビルド パフォーマンスを向上させるため 1 回だけコンパイルされます。
// コード補完や多くのコード参照機能などの IntelliSense パフォーマンスにも影響します。
// ただし、ここに一覧表示されているファイルは、ビルド間でいずれかが更新されると、すべてが再コンパイルされます。
// 頻繁に更新するファイルをここに追加しないでください。追加すると、パフォーマンス上の利点がなくなります。

#ifndef CGAL_ASSET_MODEL_PCH_H
#define CGAL_ASSET_MODEL_PCH_H

// プリコンパイルするヘッダーをここに追加します
#include "framework.h"
#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif


#include "../KIFoundation/pch.h"
using namespace KI::Foundation;

#include "../KIAsset/pch.h"
using namespace KI::Asset;

#include "CGALPolyhedron.h"
#include "CGALLinearCellComplex.h"
#include "CGALGeneralizedMaps.h"

using namespace std;
using namespace glm;

#endif //CGAL_ASSET_MODEL_PCH_H
