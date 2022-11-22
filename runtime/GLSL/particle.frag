#version 430 core
out vec4 FragColor;

in vec2 TexCoords;
in float Time;
in vec3 Position;
in vec3 Velocity;

uniform sampler2D texture_image;
uniform vec4 color;

void main()
{    
	int index = int(round(max(0.0, min(15.0, floor((2.0-Time)/2.0 * 16.0)))));
	vec2 texCoord = vec2(3-round(index/4), 3-index%4)/4 + TexCoords/4;
    FragColor = vec4(texture(texture_image, texCoord))*color;
	//FragColor = vec4(TexCoords,1, 1);
	//FragColor = vec4(vec3(texture(texture_image, TexCoords)),1);
}