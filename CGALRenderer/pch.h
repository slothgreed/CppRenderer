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

#include "Random.h"

// Foundation
#include "../KIFoundation/pch.h"
using namespace KI::Foundation;
using namespace std;
using namespace glm;

#include "BDB.h"

// utility
#include "MathHelper.h"
#include "ShaderUtility.h"
#include "FileUtility.h"


// opengl
#include "GLTypes.h"
#include "GLObject.h"
#include "GLState.h"
#include "LineState.h"
#include "PointState.h"
#include "ShaderManager.h"
#include "UniformBuffer.h"
#include "UniformScene.h"
#include "Viewport.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "Texture.h"
#include "RenderTexture.h"
#include "Sampler.h"
#include "IRenderTarget.h"
#include "RenderTarget.h"
#include "SymbolicRenderTarget.h"
#include "IUniform.h"
#include "IShaderDefine.h"
#include "IShader.h"
#include "IVertexBuffer.h"

// topology
#include "Vertex.h"
#include "HalfEdge.h"
#include "HalfEdgeFace.h"
#include "HalfEdgeVertex.h"
#include "HalfEdgeDS.h"
#include "HalfEdgeOperator.h"

// asset
#include "AssetTypes.h"
#include "Camera.h"
#include "IModel.h"
#include "IPolygonModel.h"
#include "IManipulatorModel.h"
#include "IModelProperty.h"
#include "IModelNode.h"
#include "PolygonModelNode.h"
#include "CGALModel.h"
#include "CGALPolyhedron.h"
#include "CGALLinearCellComplex.h"
#include "CGALGeneralizedMaps.h"
#include "HalfEdgeModel.h"
#include "IMaterial.h"
#include "DefaultShader.h"
#include "DefaultVertexBuffer.h"
#include "DefaultMaterial.h"
#include "OutputShader.h"
#include "OutputMaterial.h"
#include "CompositShader.h"
#include "SSLICShader.h"
#include "GrayScaleShader.h"
#include "ILight.h"
#include "DirectionLight.h"
#include "SpotLight.h"
#include "PointLight.h"
#include "IPrimitive.h"
#include "Cone.h"
#include "Cube.h"
#include "MoveManipulator.h"
#include "RotateManipulator.h"
#include "ScaleManipulator.h"
#include "ManipulatorNode.h"

// Algorithm
#include "Voxelize.h"

// Renderer
#include "PfxPlane.h"
#include "IPostEffect.h"
#include "GeometryPass.h"
#include "GrayScaleEffect.h"
#include "SSLICEffect.h"
#include "Renderer.h"
#include "PfxRenderer.h"
#include "LighthingPass.h"


// model (mvc)
#include "BDBProperty.h"
#include "NormalProperty.h"
#include "HalfEdgeProperty.h"
#include "PrimitiveNode.h"
#include "PolygonModelNode.h"
#include "HalfEdgeDSNode.h"

// application utility
#include "ModelGenerator.h"
#include "TextureGenerator.h"

// application
#include "IWorkspace.h"
#include "BunnyScene.h"
#include "CGALRenderer.h"
#include "Project.h"
#include "Workspace.h"
#include "SpecialUtility.h"

// logic
#include "CameraController.h"
#include "SubdivisionCommand.h"
#include "PickCommand.h"
#include "VoxelCommand.h"
#include "LogicEventArgs.h"



using namespace std;
using namespace glm;

#define RELEASE_INSTANCE(x) if(x != NULL) { delete x; x = NULL;}

template<class T, class U>
weak_ptr<T>
static_pointer_cast(std::weak_ptr<U> const& r)
{
	return static_pointer_cast<T>(shared_ptr<U>(r));
}


#endif //PCH_H
