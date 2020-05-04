#ifndef KI_ASSET_PCH_H
#define KI_ASSET_PCH_H

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

#include "../KIRenderer/pch.h"
using namespace KI::Renderer;

#include "../KITopology/pch.h"
using namespace KI::Topology;

// asset
#include "AssetTypes.h"
#include "IPolygonModel.h"
#include "IManipulatorModel.h"
#include "CGALModel.h"
#include "CGALPolyhedron.h"
#include "CGALLinearCellComplex.h"
#include "CGALGeneralizedMaps.h"
#include "HalfEdgeModel.h"
#include "PrimitiveModel.h"

#include "MaterialManager.h"
#include "DefaultMaterial.h"
#include "OutputMaterial.h"
#include "GeneralMaterial.h"

#include "MoveManipulator.h"
#include "RotateManipulator.h"
#include "ScaleManipulator.h"

#include "KeyFrame.h"
#include "IAnimation.h"
#include "ModelAnimation.h"
#include "Storyboard.h"



#include "GrayScaleEffect.h"
#include "SSLICEffect.h"

#endif // !KI_ASSET_PCH_H
