#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/vec4.hpp>
#include <glm/gtx/string_cast.hpp>

#include "camera.h"
#include "rendering.h"
#include "levelObject.h"

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

	GLFWwindow* mainWindow = glfwCreateWindow(winSize.x, winSize.y, "restitched", NULL, NULL);
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

	jtgTransformShader mainShader = jtgTransformShader(jtgShaderBuild("vert.vs", "frag.fs"));

	jtgShaderGroup shaderGroup = jtgShaderGroup(&mainShader);

	PathsD shapes = PathsD();
	PathD shape = PathD();

	shape.push_back(PointD(- 100, -5));
	shape.push_back(PointD(100, -5));
	shape.push_back(PointD(100, 0));
	shape.push_back(PointD(-100, 0));
	shapes.push_back(shape);

	bpLevelObject groundObject = bpLevelObject(shapes, glm::vec3(0), 5);
	shaderGroup.add(groundObject.rend);

	shapes.clear();
	shape.clear();

	shape.push_back(PointD(-1, 0));
	shape.push_back(PointD(1, 0));
	shape.push_back(PointD(1, 1));
	shape.push_back(PointD(0, 1));
	shapes.push_back(shape);

	bpLevelObject testObject = bpLevelObject(shapes, glm::vec3(0), 1);

	shaderGroup.add(testObject.rend);

	const glm::vec3 camOffset = glm::vec3(0, 1, -3);

	const float dt = 0.05f;

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(mainWindow))
	{
		t += dt;

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(.5f, 0.7f, 1, 1);

		glfwPollEvents();

		// update cam

		const glm::vec3 camOffset = glm::vec3(sin(t) * 0.2f, cos(t) * 0.2f + 1, -1);

		glm::vec3 camTargetPos = testObject.trans.pos + camOffset;
		glm::vec3 camDiff = camTargetPos - jtgCamPos;
		glm::vec3 camTargetForw = jtgCamPos - testObject.trans.pos;

		jtgCamOrient(jtgCamPos + camDiff * dt * 10.0f, testObject.trans.pos);

		// render

		shaderGroup.render();

		glfwSwapBuffers(mainWindow);
	}

	glfwTerminate();

	return 0;
}