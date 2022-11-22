#version 430 core
out vec4 FragColor;

in vec3 normal;
in vec3 position;
void main()
{
    FragColor = vec4(normal, 1.0);
} 