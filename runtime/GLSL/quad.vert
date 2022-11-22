#version 430 core
layout (location = 0) in vec2 aPos;

out vec2 TexCoords;

void main()
{
    TexCoords = aPos;
	
    gl_Position = vec4(aPos*2-vec2(1,1),0,1);
   
}