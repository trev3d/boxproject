#pragma once

#define GLM_SWIZZLE 

#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

#include <Clipper2Lib/include/clipper2/clipper.core.h>
using namespace Clipper2Lib;

std::vector<glm::vec3> computeNormals(const std::vector<glm::vec3> &verts,
	const std::vector<unsigned int> &tris);

void pathsToMesh(const Paths64 &paths, jtgMesh& mesh, const float zThick);