#pragma once

#include <vector>
#include <glm/glm.hpp>

#define JTG_FLOATS_PER_VERT 8

typedef struct jtgMesh {
	std::vector<float> verts;
	std::vector<unsigned int> tris;

	void addVert(glm::vec3 vert, glm::vec3 norm, glm::vec2 uv);
	void addTri(int a, int b, int c);
	void addQuad(int a, int b, int c, int d);
} jtgMesh;

void jtgMeshBlock(jtgMesh& mesh, glm::vec3 size);
void jtgMeshPolyhedron(jtgMesh& mesh, float radius);