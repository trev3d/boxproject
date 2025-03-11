#pragma once

#include "shader.h"

#include <vector>
#include <glm/glm.hpp>

//unsigned int debugLineShader = jtgShaderBuild("debugvert.vs", "debugfrag.fs");

struct jtgDebugDrawer {

	unsigned int vbo = 0;
	unsigned int vao = 0;

	std::vector<glm::vec3> lines;

	void draw();

};