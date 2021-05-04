#ifndef KI_TOPOLOGY_PCH_H
#define	 KI_TOPOLOGY_PCH_H

#ifndef DLL_EXPORT
#define DLL_EXPORT  __declspec(dllexport)
#endif

#pragma warning( disable : 4251 )

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
#include "Triangle.h"


#include "HalfEdge.h"
#include "HalfEdgeFace.h"
#include "HalfEdgeVertex.h"
#include "HalfEdgeDS.h"

#include "HalfEdgeOperator.h"
#include "HalfEdgeParameterIO.h"

#include "AdjancyMatrix.h"
#include "HalfEdgeAdjancyMatrix.h"
#include "AdjancyMatrixCSVIO.h"

#include "DownSampling.h"
#include "DownSamplingOperator.h"
#include "AlignOrientation.h"
#include "BVH.h"
#include "HalfEdgeRepository.h"
#include "ArrangePoint.h"

#endif // KI_TOPOLOGY_PCH_H
