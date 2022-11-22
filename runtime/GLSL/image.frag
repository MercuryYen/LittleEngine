#version 430 core
out vec4 FragColor;

in vec2 textcoord;

uniform sampler2D image;
uniform vec4 color;
uniform vec4 hoverColor;

void main()
{
    FragColor = texture(image, textcoord) * color * hoverColor;
	//FragColor = vec4(textcoord,0,1);
} 