#ifndef KI_RENDERER_PCH_H
#define KI_RENDERER_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

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


#include "Define.h"
#include "RendererTypes.h"

#include "IGLPick.h"
#include "IRaycastPick.h"

#include "IShading.h"
#include "IModel.h"
#include "IShaderPass.h"
#include "IModelProperty.h"
#include "IModelNode.h"
#include "ILight.h"
#include "IGeometryPath.h"
#include "Vertex.h"
#include "NodeOperator.h"

#include "DirectionLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include "ModelGenerator.h"
#include "TextureGenerator.h"
#include "SampleModelGenerator.h"

#include "UniformMaterial.h"
#include "UniformModel.h"
#include "UniformScene.h"
#include "UniformLight.h"


#include "ShaderCommon.h"
#include "ShaderStruct.h"
#include "DefaultVBOCode.h"
#include "DefaultVertexCode.h"
#include "DefaultVertexBuffer.h"

#include "PostProcessCode.h"
#include "SimpleShaderCode.h"

#include "ShaderManager.h"


#include "ICamera.h"
#include "PerspectiveCamera.h"
#include "OrthoCamera.h"

// Renderer
#include "PfxPlane.h"
#include "IPostEffect.h"
#include "GeometryPath.h"
#include "PickPath.h"
#include "RenderSystem.h"
#include "PfxRenderer.h"
#include "LighthingPass.h"

#include "Scene.h"

#include "RenderData.h"

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



#endif KI_RENDERER_PCH_H