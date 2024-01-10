#pragma once

#include <glm/glm.hpp>
#include "rendering.h"
#include "mesh.h"
#include "dynamics.h"

typedef struct jtgSimplePiece {
	jtgTransform transform;
	jtgMesh mesh;
	jtgMeshRenderer meshRenderer;

} jtgSimplePiece;

typedef struct jtgBlock {
	jtgTransform trans;
	jtgMeshRenderer rend;
	jtgBoxCollider col;
	jtgMesh mesh;

	jtgBlock(glm::vec3 size, jtgShaderGroup& shaderGroup, jtgPhysWorld& world);

} jtgBlock;

typedef struct jtgMarble {
	jtgTransform trans;
	jtgMesh mesh;
	jtgMeshRenderer rend;
	jtgSphereCollider col;
	jtgPhysBody body;

	jtgMarble(jtgShaderGroup& shaderGroup, jtgPhysWorld& world);

} jtgMarble;