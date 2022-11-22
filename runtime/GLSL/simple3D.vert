#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

out vec3 normal;
out vec3 position;
out vec3 oriPos;
out vec3 camPos;
void main()
{
	normal = normalize(mat3(modelMatrix) * aNormal);
	position = vec3(modelMatrix * vec4(aPos, 1.0));
	oriPos = aPos;
	camPos = vec3(inverse(viewMatrix)[3]);
    gl_Position = projectionMatrix * viewMatrix * vec4(position, 1.0);
}  