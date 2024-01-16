#pragma once

#define GLM_SWIZZLE 

#include "clipper2/clipper.h"

#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <mapbox/earcut.hpp>
#include <vector>

using namespace Clipper2Lib;

#define BP_BEVEL_POINTS 24

typedef struct bpBevel {
	glm::vec2 pointsMiterZ[BP_BEVEL_POINTS];
	bool sharp[BP_BEVEL_POINTS];
	char numPoints;

} bpBevel;

void pathsToMesh(const PathsD &paths, const bpBevel& bevel, jtgMesh& mesh, const float zThick);