#include "levelObject.h"

static float maxVertSize = 4096;

bpLevelObject::bpLevelObject(Clipper2Lib::PathsD shape, glm::vec3 pos, float zThick) {

	this->bevel = bpBevel();

	this->bevel.pointsMiterZ[0] = glm::vec2(0.1f, 0);
	this->bevel.pointsMiterZ[1] = glm::vec2(0, 0.1f);
	this->bevel.pointsMiterZ[2] = glm::vec2(0, 1);

	this->bevel.numPoints = 3;

	this->trans = jtgTransform();
	this->trans.pos = pos;
	this->trans.apply();

	this->shape = shape;
	this->zThick = zThick;

	this->rend = jtgMeshRenderer(&this->trans);

	//b2PolygonShape physShape;
	//physShape.SetAsBox(1, 1);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &physShape;
	//fixtureDef.density = 1;
	//fixtureDef.friction = 0.3f;

	updateMesh();
}



void bpLevelObject::updateMesh()
{
	pathsToMesh(this->shape, this->bevel, this->mesh, this->zThick);
	this->rend.setMesh(this->mesh);
}

glm::vec2 bpLevelObject::positionAsLocal(glm::vec2 point) {
	glm::vec4 pos(point.xy, 0, 1);
	return (glm::inverse(this->trans.mat) * pos).xy;
}

bpObjectGroup::bpObjectGroup(glm::vec3 pos)
{
	this->trans = jtgTransform();
	this->trans.pos = pos;
	this->trans.apply();

	//b2BodyDef bodyDef;
	//bodyDef.type = b2_dynamicBody;
	//bodyDef.position = b2Vec2(this->trans.pos.x, this->trans.pos.y);
	//this->body = world.CreateBody(&bodyDef);

	//b2FixtureDef fixtureDef;
	//fixtureDef.shape = &dynamicBox;
	//fixtureDef.density = 1.0f;
	//fixtureDef.friction = 0.3f;

	//body->CreateFixture(&fixtureDef);
}

void bpObjectGroup::updateCollisionShape()
{
	
}
