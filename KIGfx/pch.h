#ifndef KI_GFX_PCH_H
#define KI_GFX_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

#pragma warning( disable : 4251 )

#include<memory>
#include<string>
#include <iostream>
#include <vector>
#include<iostream>
#include<fstream>
#include <stack>
#include <assert.h>

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "../KIFoundation/pch.h"
using namespace KI::Foundation;
using namespace std;
using namespace glm;

#include "GfxTypes.h"
#include "ShaderUtility.h"
#include "GLTypes.h"

#include "IGLObject.h"
#include "UniformBuffer.h"
#include "FrameBuffer.h"
#include "RenderBuffer.h"
#include "Sampler.h"
#include "Texture.h"
#include "IndexBuffer.h"
#include "ArrayBuffer.h"


#include "IUniform.h"
#include "IShaderDefine.h"
#include "IShader.h"
#include "IVertexBuffer.h"

#include "IGLState.h"
#include "LineState.h"
#include "PointState.h"

#include "Viewport.h"
#include "RenderTexture.h"
#include "IRenderTarget.h"
#include "RenderTarget.h"
#include "SymbolicRenderTarget.h"

#endif KI_GFX_PCH_H