#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/geometric.hpp>

typedef struct jtgTransform {
	glm::vec3 pos = glm::vec3(0);
	glm::quat rot = glm::quat();
	glm::vec3 pivot = glm::vec3(0);
	float scale = 1;
	glm::mat4 mat = glm::mat4(1);

	void apply();

	jtgTransform() = default;
	jtgTransform(glm::vec3 pos);
	jtgTransform(glm::vec3 pos, glm::quat rot, float scale);

} jtgTransform;