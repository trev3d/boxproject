#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "constants.h"
#include "shader.h"
#include "transform.h"

extern glm::vec3 jtgCamPos;
extern glm::vec3 jtgCamForw;

void jtgCamSetup();
void jtgCamOrient(glm::vec3 newPos, glm::vec3 newForw);
void jtgCamTrack(glm::vec3 target);