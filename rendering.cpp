#include "rendering.h"

//#ifndef STB_IMAGE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//#endif

jtgMeshRenderer::jtgMeshRenderer(jtgTransform* trans, jtgMesh& mesh)
{
	this->trans = trans;

	glGenBuffers(1, &this->vbo);
	glGenBuffers(1, &this->ebo);
	//glGenTextures(1, &renderer.tex);

	glGenVertexArrays(1, &this->vao);
	glBindVertexArray(this->vao);

	//glBindTexture(GL_TEXTURE_2D, renderer.tex);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData);
	//glGenerateMipmap(GL_TEXTURE_2D);

	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);

	const unsigned long stride = 8 * sizeof(float);

	// position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)(0 * sizeof(float)));
	glEnableVertexAttribArray(0);

	// normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// uvs
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);

	setMesh(mesh);
}

void jtgMeshRenderer::setMesh(const jtgMesh& mesh)
{
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * mesh.verts.size(),
		&mesh.verts.front(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(int) * mesh.tris.size(),
		&mesh.tris.front(),
		GL_STATIC_DRAW);

	this->trisSize = mesh.tris.size();
}

void jtgMeshRenderer::render()
{
	//jtgShaderUse(this->shader->id);
	jtgTransformShaderCurrent->applyTransform(this->trans->mat);
	//this->shader->applyTransform(this->trans->mat);

	glBindVertexArray(this->vao);
	glDrawElements(GL_TRIANGLES, this->trisSize, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

jtgShaderGroup::jtgShaderGroup(jtgTransformShader* shader)
{
	this->shader = shader;
}

void jtgShaderGroup::add(jtgMeshRenderer renderer)
{
	this->rends.push_back(renderer);
}

void jtgShaderGroup::render()
{
	this->shader->use();
	for (int i = 0; i < this->rends.size(); i++) {
		this->rends[i].render();
	}
}

void jtgRenderGroup::add(jtgShaderGroup group)
{
	this->shaderGroups.push_back(group);
}

void jtgRenderGroup::render()
{
	for (int i = 0; i < this->shaderGroups.size(); i++) {
		this->shaderGroups[i].render();
	}
}
