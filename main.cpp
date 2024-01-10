#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/string_cast.hpp>

#include "camera.h"
#include "dynamics.h"
#include "transform.h"
#include "shader.h"
#include "rendering.h"
#include "mesh.h"

#include "gamepieces.h"

void OnFramebufferSize(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

float t;
glm::vec2 winSize = glm::vec2(800, 800);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); mac only

	GLFWwindow* mainWindow = glfwCreateWindow(winSize.x, winSize.y, "Learn openGL", NULL, NULL);
	if (mainWindow == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(mainWindow);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, winSize.x, winSize.y);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	glfwSetFramebufferSizeCallback(mainWindow, OnFramebufferSize);

	// init game

	jtgCamSetup();
	jtgCamOrient(glm::vec3(0, 1, 4), glm::vec3(0, 0, -1));

	jtgTransformShader mainShader = jtgTransformShader(jtgShaderBuild("vert.vs", "frag.fs"));

	jtgPhysCollisionGroup mainCollisionGroup;
	jtgPhysWorld physWorld = jtgPhysWorld(&mainCollisionGroup);

	jtgShaderGroup shaderGroup = jtgShaderGroup(&mainShader);

	jtgMarble marble = jtgMarble(shaderGroup, physWorld);
	marble.trans.pos = glm::vec3(0, 3, 0);
	marble.trans.apply();

	std::vector<jtgBlock> blocks;

	jtgBlock block = jtgBlock(glm::vec3(5, 1, 5), shaderGroup, physWorld);
	block.trans.pos = glm::vec3(0, -3, 0);
	block.trans.rot = glm::quat(glm::vec3(0, 0, 0.01));
	block.trans.apply();
	blocks.push_back(block);

	const glm::vec3 camOffset = glm::vec3(0, 1, -3);


	// end init

	const float dt = 0.05f;

	while (!glfwWindowShouldClose(mainWindow))
	{
		t += dt;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(.5f, 0.7f, 1, 1);

		glfwPollEvents();

		// update phys

		physWorld.step(dt);

		// reset marble if fallen

		if (marble.trans.pos.y < -10) {
			marble.trans.pos = glm::vec3(0);
			marble.trans.apply();

			marble.body.vel = glm::vec3(0);
		}

		// update cam

		glm::vec3 camTargetPos = marble.trans.pos + camOffset;
		glm::vec3 camDiff = camTargetPos - jtgCamPos;
		glm::vec3 camTargetForw = jtgCamPos - marble.trans.pos;

		jtgCamOrient(jtgCamPos + camDiff * dt * 10.0f, marble.trans.pos); 

		// render

		shaderGroup.render();

		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();

	return 0;
}