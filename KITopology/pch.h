#ifndef KI_TOPOLOGY_PCH_H
#define	 KI_TOPOLOGY_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

#pragma warning( disable : 4251 )

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


#include "IPrimitive.h"
#include "Ray.h"
#include "Sphere.h"
#include "Cone.h"
#include "Cube.h"
#include "Quad.h"
#include "Torus.h"
#include "Cylinder.h"

#include "Icosahedron.h"
#include "HalfEdge.h"
#include "HalfEdgeFace.h"
#include "HalfEdgeVertex.h"
#include "HalfEdgeDS.h"
#include "HalfEdgeOperator.h"

#endif // KI_TOPOLOGY_PCH_H
