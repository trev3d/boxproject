#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/projection.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <vector>

#include "transform.h"

typedef struct jtgPhysBody
{
	jtgTransform* trans = nullptr;

	float mass = 1;
	glm::mat3 moment = glm::mat3(0);

	glm::vec3 vel = glm::vec3(0);
	glm::vec3 angVel = glm::vec3(0);

	jtgPhysBody() = default;
	jtgPhysBody(jtgTransform* trans, float mass);

} jtgPhysBody;

typedef struct jtgBoxCollider
{
	glm::vec3 size;

	jtgTransform* trans;
	jtgPhysBody* body = nullptr;

	jtgBoxCollider() = default;
	jtgBoxCollider(jtgTransform* trans, glm::vec3 size);
	jtgBoxCollider(jtgTransform* trans, glm::vec3 size, jtgPhysBody* body);
	
} jtgBoxCollider;

typedef struct jtgSphereCollider
{
	float radius;

	jtgTransform* trans;
	jtgPhysBody* body = nullptr;

	jtgSphereCollider() = default;
	jtgSphereCollider(jtgTransform* trans, float radius);
	jtgSphereCollider(jtgTransform* trans, float radius, jtgPhysBody* body);

} jtgSphereCollider;

typedef struct jtgPhysCollision
{
	jtgPhysBody* bodyA, bodyB;
	glm::vec3 point;
	glm::vec3 norm;

} jtgPhysContact;

typedef struct jtgPhysCollisionGroup {

	std::vector<jtgBoxCollider*> boxes;
	std::vector<jtgSphereCollider*> spheres;

	void findCollisions(std::vector<jtgPhysCollision>& collisions);

} jtgPhysCollisionGroup;

typedef struct jtgPhysWorld
{
	jtgPhysCollisionGroup* collisionGroup;
	std::vector<jtgPhysBody*> bodies;
	std::vector<jtgPhysCollision> collisions;

	void step(float deltaTime);

	jtgPhysWorld(jtgPhysCollisionGroup* collisionGroup);

} jtgPhysWorld;
