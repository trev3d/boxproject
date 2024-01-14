#pragma once

#define GLM_SWIZZLE 

#include "clipper2/clipper.h"
#include "shapeMesher.h"
#include "transform.h"
#include "rendering.h"
#include "dynamics.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

struct bpLevelObject {
	jtgTransform trans;
	jtgMesh mesh;
	bpBevel bevel;
	jtgMeshRenderer rend;

	Clipper2Lib::PathsD shape;

	float zPos;
	float zThick;

	bpLevelObject(Clipper2Lib::PathsD shape, glm::vec2 pos, float zPos, float zThick);

	void updateMesh();
	glm::vec2 positionAsLocal(glm::vec2 point);
};