#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

typedef struct jtgTransformShader {
	unsigned int id;
	unsigned int transUnifLoc;

	jtgTransformShader() = default;
	jtgTransformShader(unsigned int id);

	void use();
	void applyTransform(const glm::mat4& trans);

} jtgTransformShader;

extern unsigned int jtgShaderCurrentlyBound;
extern jtgTransformShader* jtgTransformShaderCurrent;

void jtgShaderUse(unsigned int shaderId);
unsigned int jtgShaderBuild(std::string vertPath, std::string fragPath);