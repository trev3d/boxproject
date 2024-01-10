#version 330 core
out vec4 FragColor;
  
in vec3 Norm;
in vec2 UV;

void main()
{
    FragColor = vec4(Norm * (dot(Norm, vec3(0, 1, 0)) + 1) / 2, 1);
}