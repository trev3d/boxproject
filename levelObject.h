#pragma once

#define GLM_SWIZZLE 

#include "clipper2/clipper.h"

#include "shapeMesher.h"
#include "transform.h"
#include "rendering.h"
#include "phys.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace glm;

struct bpLevelObject {
	jtgTransform trans;
	jtgMesh mesh;
	bpBevel bevel;
	jtgMeshRenderer rend;

	// b2Fixture fixture;

	Clipper2Lib::PathsD shape;

	float zThick;

	bpLevelObject(Clipper2Lib::PathsD shape, glm::vec3 pos, float zThick);

	//void applyShape();
	void updateMesh();
	glm::vec2 positionAsLocal(glm::vec2 point);
};

struct bpObjectGroup {
	jtgTransform trans;

	b2Body* body;

	std::vector<bpLevelObject> levelObjects;

	bpObjectGroup(glm::vec3 pos);
	void updateCollisionShape();
};