#version 430 core
layout (location = 0) in vec2 aPos;

uniform mat3 positionMatrix;

out vec2 textcoord;

void main()
{
    gl_Position = vec4(positionMatrix * vec3(aPos,1) , 1);
	textcoord = aPos;
}  