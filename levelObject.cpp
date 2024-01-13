#include "levelObject.h"

static float maxVertSize = 4096;

LevelObject::LevelObject(Clipper2Lib::PathsD shape, glm::vec2 pos, float zPos, float zThick) {

	this->trans = jtgTransform();
	this->trans.pos.xy = pos;
	this->trans.pos.z = zPos;
	this->trans.apply();

	this->shape = shape;
	this->zThick = zThick;

	jtgMesh mesh; // todo update mesh
	this->rend = jtgMeshRenderer(&this->trans, mesh);

	pathsToMesh(this->shape, verts, tris, uvs, norms, this->zThick);
	triCount = tris.size();
}

void LevelObject::setShape(Paths shape) {
	this->shape = shape;
	pathsToMesh(shape, verts, tris, uvs, norms, zThick);
	triCount = tris.size();
	updateMesh();
}

Paths LevelObject::getShape() {
	return shape;
}

void LevelObject::setZThick(float zThick) {
	this->zThick = zThick;
	pathsToMesh(shape, verts, tris, uvs, norms, zThick);
	updateMesh();
}

glm::vec2 LevelObject::positionAsLocal(glm::vec2 point) {
	glm::vec4 pos(point.xy, 0, 1);
	return (glm::inverse(this->transform) * pos).xy;
}