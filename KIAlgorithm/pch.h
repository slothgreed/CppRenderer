#ifndef KI_ALGORITHM_PCH_H
#define KI_ALGORITHM_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  //__declspec(dllexport)
#endif


#include "../KIFoundation/pch.h"
using namespace KI::Foundation;

#include "../KITopology/pch.h"
using namespace KI::Topology;

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
using namespace std;
using namespace glm;

#include "Voxelize.h"

#endif //KI_ALGORITHM_PCH_H
