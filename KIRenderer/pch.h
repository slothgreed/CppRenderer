#ifndef KI_RENDERER_PCH_H
#define KI_RENDERER_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

#include "../KIFoundation/pch.h"
using namespace KI::Foundation;

#include "../KIGfx/pch.h"
using namespace KI::Gfx;

#include "../KIShaderLib/pch.h"
using namespace KI::ShaderLib;

#include "RendererEventArgs.h"
#include "RendererTypes.h"

#include "IModel.h"


#include "IModelProperty.h"
#include "IModelNode.h"
#include "Vertex.h"
#include "NodeOperator.h"

#include "ILight.h"
#include "DirectionLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include "TextureGenerator.h"

#include "ShaderManager.h"


#include "ICamera.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"
#include "CameraUtility.h"

// Renderer
#include "IRenderPath.h"
#include "IPostEffect.h"

#include "RenderSystem.h"
#include "PfxRenderer.h"
#include "RenderData.h"
#include "Material.h"
#include "Scene.h"

#include "PickPath.h"
#include "OutputPath.h"


#include "TextureManager.h"
#include "GfxResource.h"

#endif KI_RENDERER_PCH_H