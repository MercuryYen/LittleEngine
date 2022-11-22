#version 430 core
out vec4 FragColor;

in vec2 textcoord;

uniform vec2 size;
uniform vec4 color;
uniform sampler2DRect letter;

void main()
{
    FragColor = vec4(1,1,1,texture(letter, floor(textcoord*size)).r)*color;
	//FragColor = vec4(textcoord,0,1);
} 