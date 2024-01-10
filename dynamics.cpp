#include "dynamics.h"

using namespace glm;

jtgPhysBody staticBody;

float clamp(const float& f, const float& min, const float& max) {
	return std::max(min, std::min(f, max));
}

vec3 ClampToBox(const glm::vec3& pos, const glm::vec3& size) {
	const vec3 extents = size * 0.5f;

	vec3 p = pos;

	p.x = clamp(p.x, -extents.x, extents.x);
	p.y = clamp(p.y, -extents.y, extents.y);
	p.z = clamp(p.z, -extents.z, extents.z);

	return p;
}

bool SphereOnBox(const jtgSphereCollider& sphere, const jtgBoxCollider& box, jtgPhysCollision& contact) {

	const vec3 sphereLocal = vec3((inverse(box.trans->mat) * sphere.trans->mat)[3]);
	const vec3 closestLocal = ClampToBox(sphereLocal, box.size);

	const bool areTouching = distance(closestLocal, sphereLocal) <= sphere.radius;

	if (areTouching)
	{
		const vec3 closestWorld = vec3(box.trans->mat * vec4(closestLocal, 1));
		contact.point = closestWorld;
		contact.norm = normalize(sphere.trans->pos - closestWorld);
	}

	return areTouching;
}

vec3 VelAtPoint(const jtgPhysBody& body, const vec3& point)
{
	return body.vel + cross(point - body.trans->pos, body.angVel);
}

void jtgPhysCollisionGroup::findCollisions(std::vector<jtgPhysCollision>& collisions)
{
	collisions.clear();

	// sphere on box only for now
	for (int s = 0; s < this->spheres.size(); s++)
	{
		const jtgSphereCollider* sphere = this->spheres[s];

		for (int b = 0; b < this->boxes.size(); b++)
		{
			const jtgBoxCollider* box = this->boxes[b];

			jtgPhysCollision collision;
			collision.bodyA = sphere->body;

			if (SphereOnBox(*sphere, *box, collision)) {
				collisions.push_back(collision);
			}
		}
	}
}

jtgPhysWorld::jtgPhysWorld(jtgPhysCollisionGroup* collisionGroup)
{
	this->collisionGroup = collisionGroup;
}

void jtgPhysWorld::step(float deltaTime) {

	this->collisionGroup->findCollisions(this->collisions);
	
	for (int i = 0; i < this->collisions.size(); i++)
	{
		jtgPhysCollision contact = this->collisions[i];

		// no support for other body yet
		// one sphere in static world

		if (dot(contact.bodyA->vel, contact.norm) > 0)
			continue;

		vec3 impulse = proj(-(contact.bodyA->vel), contact.norm);

		contact.bodyA->vel += impulse;
		
		// todo depenetration
	}

	const vec3 grav = vec3(0, -9.81f * deltaTime, 0);

	for (int i = 0; i < this->bodies.size(); i++)
	{
		jtgPhysBody* body = this->bodies[i];

		// apply velocity
		body->trans->pos += body->vel * deltaTime;
		body->trans->apply();

		// gravity applied for next step
		body->vel += grav;
	}
}

jtgPhysBody::jtgPhysBody(jtgTransform* trans, float mass)
{
	this->trans = trans;
	this->mass = mass;
}

jtgBoxCollider::jtgBoxCollider(jtgTransform* trans, glm::vec3 size)
{
	this->trans = trans;
	this->size = size;
}

jtgBoxCollider::jtgBoxCollider(jtgTransform* trans, glm::vec3 size, jtgPhysBody* body)
{
	this->trans = trans;
	this->size = size;
	this->body = body;
}

jtgSphereCollider::jtgSphereCollider(jtgTransform* trans, float radius)
{
	this->trans = trans;
	this->radius = radius;
}

jtgSphereCollider::jtgSphereCollider(jtgTransform* trans, float radius, jtgPhysBody* body)
{
	this->trans = trans;
	this->radius = radius;
	this->body = body;
}
