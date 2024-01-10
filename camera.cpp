#include "camera.h"

glm::vec3 jtgCamPos;
glm::vec3 jtgCamForw;

unsigned int ubo;
glm::mat4 proj;
glm::mat4 mat;

void updateUbo() {
	int size = sizeof(glm::mat4);

	glBindBuffer(GL_UNIFORM_BUFFER, ubo);

	glBufferData(GL_UNIFORM_BUFFER, 2 * size, NULL, GL_STATIC_DRAW);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, size, glm::value_ptr(proj));
	glBufferSubData(GL_UNIFORM_BUFFER, size, size, glm::value_ptr(mat));

	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void jtgCamSetup() {
	proj = glm::perspective(90.0, 1.0, 0.01, 100.0);

	glGenBuffers(1, &ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBufferData(GL_UNIFORM_BUFFER, 128, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	glBindBuffer(GL_UNIFORM_BUFFER, ubo);
	glBindBufferRange(GL_UNIFORM_BUFFER, 0, ubo, 0, 2 * sizeof(glm::mat4));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	updateUbo();
}

void jtgCamOrient(glm::vec3 newPos, glm::vec3 newForw)
{
	jtgCamPos = newPos;
	jtgCamForw = newForw;
	mat = glm::lookAt(jtgCamPos, jtgCamForw, worldUp);
	updateUbo();
}

void jtgCamTrack(glm::vec3 target)
{
	jtgCamOrient(jtgCamPos, glm::normalize(target - jtgCamPos));
}