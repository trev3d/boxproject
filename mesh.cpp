#include "mesh.h"

#include <glm/glm.hpp>

void jtgMeshBlock(jtgMesh& mesh, glm::vec3 size) {

	glm::vec3 ax = size * .5f;

	glm::vec3 in = -ax;

	mesh.verts = {
		// pos   norm      uv
		// bottom
		in.x, in.y, in.z, 0, -1, 0, size.x, 0, // 0
		ax.x, in.y, in.z, 0, -1, 0, 0, 0, // 1
		ax.x, in.y, ax.z, 0, -1, 0, 0,size.z, // 2
		in.x, in.y, ax.z, 0, -1, 0, size.x, size.z, // 3

		// top
		in.x, ax.y, in.z, 0, 1, 0, 0, 0, // 4
		in.x, ax.y, ax.z, 0, 1, 0, 0, size.z, // 5
		ax.x, ax.y, ax.z, 0, 1, 0, size.x, size.z, // 6
		ax.x, ax.y, in.z, 0, 1, 0, size.x, 0, // 7

		// left
		in.x, in.y, in.z, -1, 0, 0, 0, size.y, // 8
		in.x, in.y, ax.z, -1, 0, 0, size.z, size.y, // 9
		in.x, ax.y, ax.z, -1, 0, 0, size.z, 0, // 10
		in.x, ax.y, in.z, -1, 0, 0, 0, 0, // 11

		// right
		ax.x, in.y, in.z, 1, 0, 0, size.z, size.y, // 12
		ax.x, ax.y, in.z, 1, 0, 0, size.z, 0, // 13
		ax.x, ax.y, ax.z, 1, 0, 0, 0, 0, // 14
		ax.x, in.y, ax.z, 1, 0, 0, 0, size.y, // 15

		// back
		in.x, in.y, in.z, 0, 0, -1, size.x, size.y, // 16
		in.x, ax.y, in.z, 0, 0, -1, size.x, 0, // 18
		ax.x, ax.y, in.z, 0, 0, -1, 0, 0, // 18
		ax.x, in.y, in.z, 0, 0, -1, 0, size.y, // 19

		// front
		in.x, in.y, ax.z, 0, 0, 1, 0, size.y, // 20
		ax.x, in.y, ax.z, 0, 0, 1, size.x, size.y, // 21
		ax.x, ax.y, ax.z, 0, 0, 1, size.x, 0, // 22
		in.x, ax.y, ax.z, 0, 0, 1, 0, 0, // 23
	};

	mesh.tris = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20,
	};
}

void jtgMeshPolyhedron(jtgMesh& mesh, float r)
{
	const float t = (1.f + sqrt(5.f)) * .5f;

	const float b = r;
	const float a = b / t;

	mesh.verts = {
		 b,  a,  0,  t,  1,  0, 0, 0,
		-b,  a,  0, -t,  1,  0, 0, 0,
		 b, -a,  0,  t, -1,  0, 0, 0,
		-b, -a,  0, -t, -1,  0, 0, 0,
		 a,  0,  b,  1,  0,  t, 0, 0,
		 a,  0, -b,  1,  0, -t, 0, 0,
		-a,  0,  b, -1,  0,  t, 0, 0,
		-a,  0, -b, -1,  0, -t, 0, 0,
		 0,  b,  a,  0,  t,  1, 0, 0,
		 0, -b,  a,  0, -t,  1, 0, 0,
		 0,  b, -a,  0,  t, -1, 0, 0,
		 0, -b, -a,  0, -t, -1, 0, 0,
	};

	mesh.tris = {
		0, 8, 4,
		0, 5, 10,
		2, 4, 9,
		2, 11, 5,
		1, 6, 8,
		1, 10, 7,
		3, 9, 6,
		3, 7, 11,
		0, 10, 8,
		1, 8, 10,
		2, 9, 11,
		3, 9, 11,
		4, 2, 0,
		5, 0, 2,
		6, 1, 3,
		7, 3, 1,
		8, 6, 4,
		9, 4, 6,
		10, 5, 7,
		11, 7, 5,
	};
}

void jtgMesh::addVert(glm::vec3 vert, glm::vec3 norm, glm::vec2 uv)
{
	this->verts.push_back(vert.x);
	this->verts.push_back(vert.y);
	this->verts.push_back(vert.z);

	this->verts.push_back(norm.x);
	this->verts.push_back(norm.y);
	this->verts.push_back(norm.z);

	this->verts.push_back(uv.x);
	this->verts.push_back(uv.y);
}

void jtgMesh::setNorm(int index, glm::vec3 norm)
{
	int i = index * JTG_FLOATS_PER_VERT;

	this->verts[i + 3] = norm.x;
	this->verts[i + 4] = norm.y;
	this->verts[i + 5] = norm.z;
}

void jtgMesh::addTri(int a, int b, int c)
{
	this->tris.push_back(a);
	this->tris.push_back(b);
	this->tris.push_back(c);
}

void jtgMesh::addQuad(int a, int b, int c, int d)
{
	addTri(a, b, c);
	addTri(b, a, d);
}
