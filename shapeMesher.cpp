#include "shapeMesher.h"

namespace mapbox {
	namespace util {
		template <>
		struct nth<0, PointD> {
			inline static auto get(const PointD& t) {
				return t.x;
			};
		};
		template <>
		struct nth<1, PointD> {
			inline static auto get(const PointD& t) {
				return t.y;
			};
		};

		template <>
		struct nth<0, glm::vec2> {
			inline static auto get(const glm::vec2& t) {
				return t.x;
			};
		};
		template <>
		struct nth<1, glm::vec2> {
			inline static auto get(const glm::vec2& t) {
				return t.y;
			};
		};
	}
}

PointD inline vecToPoint(glm::vec2 vec) {
	return PointD(vec.x, vec.y);
}

glm::vec2 inline pointToVec(PointD point) {
	return glm::vec2(point.x, point.y);
}

void pathsToMesh(const PathsD& paths, const bpBevel& bevel, jtgMesh& mesh, const float zThick) {

	mesh.verts.clear();
	mesh.tris.clear();

	std::vector<std::vector<glm::vec2>> offsetPaths(paths.size(), std::vector<glm::vec2>());

	int k = 0;

	for (int l = 0; l < paths.size(); l++)
	{
		PathD path = paths[l];
		std::vector<glm::vec2> offsetPath(path.size(), glm::vec2());

		int c = bevel.numPoints;

		for (int i = 0; i < bevel.numPoints; i++) {
			if (bevel.sharp[i])
				c++;
		}

		//bevels

		//front face offset inward
		float frontZ = bevel.pointsMiterZ[0].y;

		for (int i = 0; i < path.size(); i++)
		{
			//front face vertex position
			glm::vec2 insetPoint = glm::vec2(path[i].x, path[i].y);

			//next index
			int j = (i + 1) % path.size();

			//normal A
			glm::vec2 normNext = glm::vec2(path[i].y - path[j].y, path[j].x - path[i].x);
			normNext = glm::normalize(normNext);

			//previous index
			j = (i - 1);
			if (j < 0)
				j += path.size();

			//normal B
			glm::vec2 normPrev = glm::vec2(path[j].y - path[i].y, path[i].x - path[j].x);
			normPrev = glm::normalize(normPrev);

			//bevel direction and magnitude
			glm::vec2 miter = glm::normalize(normNext + normPrev);
			miter *= 1.41421f / sqrt(1 + glm::dot(normNext, normPrev));

			insetPoint += miter * bevel.pointsMiterZ[0].x;

			offsetPath[i] = insetPoint;

			// create quad strips down z of object

			float angle = glm::degrees(acos(dot(normNext, normPrev)));
			bool sharpCorner = angle > 30;

#define GET_POINT(index, z) glm::vec3(insetPoint + miter * (bevel.pointsMiterZ[index].x - frontZ), z);

#define ADD_VERT(norm)\
	float frontZ = bevel.pointsMiterZ[0].x;\
	float z1 = bevel.pointsMiterZ[bevelIndex].y;\
	float z2;\
	if (bevelIndex == bevel.numPoints - 2)\
		z2 = zThick;\
	else\
		z2 = bevel.pointsMiterZ[bevelIndex + 1].y;\
	glm::vec3 vert = GET_POINT(bevelIndex, z1);\
	mesh.addVert(vert, glm::vec3(0, 1, 0), vert.xy);\
	if (bevelIndex == bevel.numPoints - 2)\
	{\
		vert = GET_POINT(bevelIndex + 1, z2);\
		mesh.addVert(vert, glm::vec3(0, 1, 0), (insetPoint + norm * (z1 - z2)).xy);\
	}\
	else if (bevel.sharp[bevelIndex + 1])\
	{\
		vert = GET_POINT(bevelIndex + 1, z2);\
		mesh.addVert(vert, glm::vec3(0, 1, 0), vert.xy);\
	}\

			if (sharpCorner) {

				for (int bevelIndex = 0; bevelIndex < bevel.numPoints - 1; bevelIndex++)
				{
					ADD_VERT(normPrev);
				}
			}

			int a = 0;

			for (int bevelIndex = 0; bevelIndex < bevel.numPoints - 1; bevelIndex++)
			{
				if (bevel.sharp[bevelIndex])
					a++;

				int numVerts = mesh.verts.size() / JTG_FLOATS_PER_VERT;

				if (i == path.size() - 1)
				{
					mesh.addQuad(k + bevelIndex + a, numVerts + 1, numVerts, k + bevelIndex + a + 1);
				}
				else
				{
					mesh.addQuad(numVerts + c, numVerts + 1, numVerts, numVerts + c + 1);
				}

				//add vertices
				ADD_VERT(normNext);
			}
		}

		offsetPaths[l] = offsetPath;

		k = mesh.verts.size() / JTG_FLOATS_PER_VERT;
	}

	//norms = computeNormals(verts, tris);

	// front face

	for (unsigned int i = 0; i < offsetPaths[0].size(); i++) {
		glm::vec2 v = offsetPaths[0][i];
		mesh.addVert(glm::vec3(v, 0), glm::vec3(0, 0, 1), v);
	}

	std::vector<unsigned int> frontTris = mapbox::earcut<unsigned int>(paths);
	for (int i = frontTris.size() - 1; i > -1; i--) {
		mesh.tris.push_back(frontTris[i] + k);
	}
}

#undef GET_POINT
#undef ADD_VERT