#include "levelObject.h"

static float maxVertSize = 4096;

bpLevelObject::bpLevelObject(Clipper2Lib::PathsD shape, glm::vec2 pos, float zPos, float zThick) {

	this->trans = jtgTransform();
	this->trans.pos.xy = pos;
	this->trans.pos.z = zPos;
	this->trans.apply();

	this->shape = shape;
	this->zThick = zThick;

	jtgMesh mesh; // todo update mesh
	this->rend = jtgMeshRenderer(&this->trans);

	updateMesh();
}

void bpLevelObject::updateMesh()
{
	pathsToMesh(this->shape, this->mesh, this->zThick);
	this->rend.setMesh(this->mesh);
}

glm::vec2 bpLevelObject::positionAsLocal(glm::vec2 point) {
	glm::vec4 pos(point.xy, 0, 1);
	return (glm::inverse(this->trans.mat) * pos).xy;
}