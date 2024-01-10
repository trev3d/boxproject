#include "gamepieces.h"

jtgBlock::jtgBlock(glm::vec3 size, jtgShaderGroup& shaderGroup, jtgPhysWorld& world)
{
	this->trans = jtgTransform();
	this->col = jtgBoxCollider(&this->trans, size);
	jtgMeshBlock(this->mesh, size);
	this->rend = jtgMeshRenderer(&this->trans, this->mesh);

	world.collisionGroup->boxes.push_back(&this->col);
	shaderGroup.add(this->rend);
}

jtgMarble::jtgMarble(jtgShaderGroup& shaderGroup, jtgPhysWorld& world)
{
	this->trans = jtgTransform();
	
	float rad = .5f;

	this->body = jtgPhysBody(&this->trans, 1);
	this->col = jtgSphereCollider(&this->trans, rad, &this->body);
	jtgMeshPolyhedron(this->mesh, rad);
	this->rend = jtgMeshRenderer(&this->trans, this->mesh);

	world.collisionGroup->spheres.push_back(&this->col);
	world.bodies.push_back(&this->body);
	shaderGroup.add(this->rend);
}