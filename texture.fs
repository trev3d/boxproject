#version 330 core
out vec4 FragColor;
  
in vec3 Norm;
in vec2 UV;

uniform sampler2D Tex;

void main()
{
    FragColor = texture(Tex, UV) * (dot(Norm, vec3(0, 1, 0)) + 1) / 2;
}