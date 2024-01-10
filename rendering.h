#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "transform.h"
#include "shader.h"
#include "mesh.h"

typedef struct jtgMeshRenderer {

	unsigned int vbo = 0;
	unsigned int vao = 0;
	unsigned int ebo = 0;
	unsigned int tex = 0;
	unsigned int trisSize = 0;

	jtgTransform* trans = nullptr;

	jtgMeshRenderer() = default;
	jtgMeshRenderer(jtgTransform* trans, jtgMesh& mesh);

	void setMesh(const jtgMesh& mesh);
	void render();

} jtgMeshRenderer;

typedef struct jtgShaderGroup {

	jtgTransformShader* shader = nullptr;

	std::vector<jtgMeshRenderer> rends;

	jtgShaderGroup() = default;
	jtgShaderGroup(jtgTransformShader* shader);

	void add(jtgMeshRenderer renderer);
	void render();
} jtgShaderGroup;

typedef struct jtgRenderGroup {
	std::vector<jtgShaderGroup> shaderGroups;

	void add(jtgShaderGroup group);
	void render();
};