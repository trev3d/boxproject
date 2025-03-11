#version 330 core

layout (location = 0) in vec3 aPos;

out vec4 Color;

layout (std140) uniform Cam
{
	mat4 proj; // 16 * 4 // 0
	mat4 view; // 16 * 4 // 64 
};

uniform mat4 trans;

void main()
{
	gl_Position = proj * view * trans * vec4(aPos, 1.0);
}