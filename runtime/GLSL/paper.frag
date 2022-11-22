#version 430 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture_image;

float rand(vec2 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	vec3 ori = texture(texture_image, TexCoords).rgb;
	vec3 up = texture(texture_image, TexCoords + 0.1*vec2(0,0.0192)).rgb;
	vec3 down = texture(texture_image, TexCoords + 0.1*vec2(0,-0.0192)).rgb;
	vec3 right = texture(texture_image, TexCoords + 0.1*vec2(0.0108,0)).rgb;
	vec3 left = texture(texture_image, TexCoords + 0.1*vec2(-0.0108,0)).rgb;
	vec3 edger = 2*ori-(up+down+right+left)/2;
	float power = clamp((abs(edger.r)+abs(edger.g)+abs(edger.b))/3,0,1);
	
	FragColor = vec4(vec3(1,0.976,0.749)-vec3(rand(TexCoords))*0.2,1);
	if(power>0.1){
		FragColor -= vec4(vec3(power),1);
	}
	
	//float r = length(TexCoords - vec2(0.5,0.5));
	//float rnd = rand(vec2(r,r));
	//FragColor = vec4(texture(texture_image, TexCoords*0.8+vec2(0.1,0.1)))*color + vec4(1,1,1,1) * pow(rnd, 2) * length(TexCoords - vec2(0.5,0.5));
	//vec4 text = texture(texture_image, TexCoords*0.8+vec2(0.1,0.1));
	//FragColor = text*color	 + vec4(1,0.72,0.89,0.3) * pow(rnd, 4) * text.a + vec4(1,0.72,0.89,1) * pow(rnd, 4) * text.a;
	//FragColor = vec4(TexCoords,1, 1);
	//FragColor = texture(texture_image, TexCoords);
}