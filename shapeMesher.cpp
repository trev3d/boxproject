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

PointD vecToPoint(glm::vec2 vec) {
	return PointD(vec.x, vec.y);
}

glm::vec2 pointToVec(PointD point) {
	return glm::vec2(point.x, point.y);
}

std::vector<glm::vec3> computeNormals(const std::vector<glm::vec3>& verts,
	const std::vector<unsigned int>& tris) {

	std::vector<glm::vec3> norms = std::vector<glm::vec3>(verts.size(), glm::vec3());

	// cross products
	for (unsigned int i = 0; i < tris.size(); i += 3) {
		glm::vec3 v1 = verts[tris[i]] - verts[tris[i + 1]];
		glm::vec3 v2 = verts[tris[i + 1]] - verts[tris[i + 2]];
		norms[tris[i + 1]] += glm::cross(v1, v2);

		v1 = verts[tris[i + 1]] - verts[tris[i + 2]];
		v2 = verts[tris[i + 2]] - verts[tris[i]];
		norms[tris[i + 2]] += glm::cross(v1, v2);

		v1 = verts[tris[i + 2]] - verts[tris[i]];
		v2 = verts[tris[i]] - verts[tris[i + 1]];
		norms[tris[i]] += glm::cross(v1, v2);
	}


	// normalize all
	for (int i = 0; i < norms.size(); i++) {
		norms[i] = glm::normalize(norms[i]);
	}

	return norms;
}

void pathsToMesh(const PathsD &paths,jtgMesh& mesh,const float zThick) {

	mesh.verts.clear();
	mesh.tris.clear();

	//verts.clear();
	//tris.clear();
	//uvs.clear();
	//norms.clear();

	// placeholder bevel 
	glm::vec2 bp[] = {
		glm::vec2(0.2f, 0),
		glm::vec2(0.1f, 0),
		glm::vec2(0.02928932188f, 0.02928932188f),
		glm::vec2(0, 0.1f),
		glm::vec2(0, 1),
	};
	int bpSize = 5;

	bool s[] = {
		false,
		false,
		false,
		false,
		false,
	};

	/*glm::vec2 bp[] = {
		glm::vec2(0, 0),
		glm::vec2(0, 1),
	};
	int bpSize = 2;

	bool s[] = {
		false,
		false,
	};*/

	std::vector<std::vector<glm::vec2>> offsetPaths(paths.size(), std::vector<glm::vec2>());

	int k = 0;

	//bevels
	for (int l = 0; l < paths.size(); l++)
	{
		PathD path = paths[l];
		std::vector<glm::vec2> offsetPath(path.size(), glm::vec2());

		int c = bpSize;

		for (int i = 0; i < bpSize; i++) {
			if (s[i])
				c++;
		}

		//bevels

		//front face offset inward
		float o = bp[0].x;

		for (int i = 0; i < path.size(); i++)
		{
			//front face vertex position
			glm::vec3 v;
			v.xy = pointToVec(path[i]);

			//next index
			int j = (i + 1) % path.size();

			//normal A
			glm::vec2 na = pointToVec(PointD(path[i].y - path[j].y, path[j].x - path[i].x));
			na = glm::normalize(na);

			//previous index
			j = (i - 1);
			if (j < 0)
				j += path.size();

			//normal B
			glm::vec2 nb = pointToVec(PointD(path[j].y - path[i].y, path[i].y - path[j].y));
			nb = glm::normalize(nb);

			//bevel direction and magnitude
			glm::vec3 b = glm::vec3(glm::normalize(na + nb), 0);
			b *= 1.41421f / sqrt(1 + glm::dot(na, nb));

			v += b * bp[0].x;

			offsetPath[i] = v;

			float angle = glm::degrees(acos(dot(na, nb)));
			bool sh = angle > 30;

			if (sh)

				for (int n = 0; n < bpSize - 1; n++)
				{
					//z offset
					glm::vec3 z(0, 0, bp[n].y);
					glm::vec3 z2;
					if (n == bpSize - 2)
						z2 = glm::vec3(0, 0, zThick);
					else
						z2 = glm::vec3(0, 0, bp[n + 1].y);

					glm::vec3 nbv3 = glm::vec3(nb, 0);
					glm::vec3 nn = v + nbv3 * (z.z - z2.z);
					//
					// int a = 1;
					//
					// if (s[n + 1])
					glm::vec3 vert = v + b * (bp[n].x - o) + z;
					mesh.verts.push_back(vert.x);
					mesh.verts.push_back(vert.y);
					mesh.verts.push_back(vert.z);

					//uvs.push_back(verts.at(verts.size() - 1));

					if (n == bpSize - 2)
					{
						glm::vec3 vert = v + b * (bp[n + 1].x - o) + z2;
						mesh.verts.push_back(vert.x);
						mesh.verts.push_back(vert.y);
						mesh.verts.push_back(vert.z);
						//uvs.push_back(nn);
					}
					else if (s[n + 1])
					{
						glm::vec3 vert = v + b * (bp[n + 1].x - o) + z2;
						mesh.verts.push_back(vert.x);
						mesh.verts.push_back(vert.y);
						mesh.verts.push_back(vert.z);
						//uvs.push_back(verts.at(verts.size() - 1));
					}
				}

			int a = 0;

			for (int n = 0; n < bpSize - 1; n++)
			{
				//z offset
				glm::vec3 z(0, 0, bp[n].y);
				glm::vec3 z2;
				if (n == bpSize - 2)
					z2 = glm::vec3(0, 0, zThick);
				else
					z2 = glm::vec3(0, 0, bp[n + 1].y);

				glm::vec3 nn;
				if (sh)
					nn = v + (na, 0) * (z.z - z2.z);
				else
				{
					nn = v + glm::normalize(b) * (z.z - z2.z);
				}

				if (s[n])
					a++;

				int vsize = mesh.verts.size();

				if (i == path.size() - 1)
				{
					mesh.tris.push_back(k + n + a);
					mesh.tris.push_back(vsize + 1);
					mesh.tris.push_back(vsize);

					mesh.tris.push_back(vsize + 1);
					mesh.tris.push_back(k + n + a);
					mesh.tris.push_back(k + n + a + 1);
				}
				else
				{
					mesh.tris.push_back(vsize + c);
					mesh.tris.push_back(vsize + 1);
					mesh.tris.push_back(vsize);

					mesh.tris.push_back(vsize + 1);
					mesh.tris.push_back(vsize + c);
					mesh.tris.push_back(vsize + c + 1);
				}

				//add vertices
				glm::vec3 vert = v + b * (bp[n].x - o) + z;
				mesh.verts.push_back(vert.x);
				mesh.verts.push_back(vert.y);
				mesh.verts.push_back(vert.z);

				// ad uvs
				/*uvs.push_back(verts.at(verts.size() - 1));*/
				mesh.verts.push_back(mesh.verts.at(mesh.verts.size() - 3));
				mesh.verts.push_back(mesh.verts.at(mesh.verts.size() - 2));
				mesh.verts.push_back(mesh.verts.at(mesh.verts.size() - 1));

				if (n == bpSize - 2)
				{
					glm::vec3 vert = v + b * (bp[n + 1].x - o) + z2;
					mesh.verts.push_back(vert.x);
					mesh.verts.push_back(vert.y);
					mesh.verts.push_back(vert.z);
					//uvs.push_back(nn);
				}
				else if (s[n + 1])
				{
					glm::vec3 vert = v + b * (bp[n + 1].x - o) + z2;
					mesh.verts.push_back(vert.x);
					mesh.verts.push_back(vert.y);
					mesh.verts.push_back(vert.z);
					//uvs.push_back(verts.at(verts.size() - 1));
				}
			}
		}

		offsetPaths[l] = offsetPath;

		k = mesh.verts.size();
	}

	//norms = computeNormals(verts, tris);

	// front face

	for (unsigned int i = 0; i < offsetPaths[0].size(); i++) {
		glm::vec3 vert = glm::vec3(offsetPaths[0][i], 0);
		mesh.verts.push_back(vert.x);
		mesh.verts.push_back(vert.y);
		mesh.verts.push_back(vert.z);
		//uvs.push_back(offsetPaths[0][i]);
		//norms.push_back(glm::vec3(0, 0, -1));
	}

	std::vector<unsigned int> frontTris = mapbox::earcut<unsigned int>(paths);
	for (int i = frontTris.size() - 1; i > -1; i--) {
		mesh.tris.push_back(frontTris[i] + k);
	}
}