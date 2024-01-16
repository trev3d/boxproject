#include "phys.h"

b2Body* groundBody;

void setupPhysWorld() {
	b2Vec2 gravity(0, -10);
	world = b2World(gravity);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, -10);
	groundBody = world.CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50, 10);

	groundBody->CreateFixture(&groundBox, 0);
}