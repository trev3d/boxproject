#pragma once

#include <vector>
#include <glm/glm.hpp>

typedef struct jtgMesh {
	std::vector<float> verts;
	std::vector<unsigned int> tris;
} jtgMesh;

void jtgMeshBlock(jtgMesh& mesh, glm::vec3 size);
void jtgMeshPolyhedron(jtgMesh& mesh, float radius);