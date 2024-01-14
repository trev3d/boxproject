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

std::vector<glm::vec3> computeNormals(const std::vector<glm::vec3> &verts,
	const std::vector<unsigned int> &tris);

void pathsToMesh(const PathsD &paths, jtgMesh& mesh, const float zThick);