#ifndef KI_RENDERER_PCH_H
#define KI_RENDERER_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  //__declspec(dllexport)
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

#include "IModel.h"
#include "IMaterial.h"
#include "IModelProperty.h"
#include "IModelNode.h"
#include "IMaterial.h"
#include "ILight.h"

#include "Vertex.h"
#include "DirectionLight.h"
#include "SpotLight.h"
#include "PointLight.h"

#include "ModelGenerator.h"
#include "TextureGenerator.h"

#include "UniformScene.h"
#include "UniformLight.h"
#include "DefaultShader.h"
#include "DefaultVertexBuffer.h"
#include "OutputShader.h"
#include "CompositShader.h"
#include "SSLICShader.h"
#include "GrayScaleShader.h"
#include "ShaderManager.h"

#include "Camera.h"
// Renderer
#include "PfxPlane.h"
#include "IPostEffect.h"
#include "GeometryPass.h"
#include "GrayScaleEffect.h"
#include "SSLICEffect.h"
#include "RenderSystem.h"
#include "PfxRenderer.h"
#include "LighthingPass.h"

#endif KI_RENDERER_PCH_H