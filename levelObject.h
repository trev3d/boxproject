#pragma once

#define GLM_SWIZZLE 

#include "shapeMesher.h"
#include "transform.h"
#include "rendering.h"
#include "dynamics.h"
#include "mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Clipper2Lib/include/clipper2/clipper.h>
#include <Clipper2Lib/include/clipper2/clipper.core.h>

using namespace glm;

struct LevelObject {
	jtgTransform trans;
	jtgMesh mesh;
	jtgMeshRenderer rend;

	Clipper2Lib::PathsD shape;

	float zPos;
	float zThick;

	LevelObject(Clipper2Lib::PathsD shape, glm::vec2 pos, float zPos, float zThick);

	void updateMesh();
	void setShape(PathD shape);
	void setZThick(float zThick);
	void addPoint(PointD point);
	void addPointWorldSpace(glm::vec2 point);
	glm::vec2 positionAsLocal(glm::vec2 point);
};