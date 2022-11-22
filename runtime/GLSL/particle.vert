#version 430 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in float aTime;
layout (location = 2) in vec3 aPosition;
layout (location = 3) in vec3 aVelocity;

out vec2 TexCoords;
out float Time;
out vec3 Position;
out vec3 Velocity;

uniform mat4 individualMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    TexCoords = aPos;
	Time = aTime;
	Position = aPosition;
	Velocity = aVelocity;
	
	//remove rotation
    mat4 modelMatrix2 = mat4(1.0);
	modelMatrix2[3] = modelMatrix[3];
	
	mat4 viewMatrix2 = mat4(1.0);
	viewMatrix2[3] = viewMatrix[3];
    gl_Position = projectionMatrix * (viewMatrix * modelMatrix2 * vec4(aPosition,1) + individualMatrix * vec4(aPos, 0, 0));
   
}