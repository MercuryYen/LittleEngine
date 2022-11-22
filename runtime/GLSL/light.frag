#version 430 core
out vec4 FragColor;
uniform vec3 DirectionalLightDirection;
uniform vec3 diffuseColor;
uniform vec3 ambientColor;

in vec3 normal;
in vec3 position;
in vec3 oriPos;
in vec3 camPos;

float CalcDirLight(vec3 dld, vec3 n, vec3 vd);

void main()
{
	float result = CalcDirLight(DirectionalLightDirection, normalize(normal), normalize(camPos - position));
    FragColor = vec4(result * diffuseColor + ambientColor, 1.0);
} 

float CalcDirLight(vec3 dld, vec3 n, vec3 vd)
{
    vec3 lightDir = normalize(-dld);
    vec3 reflectDir = reflect(-lightDir, n);
    return pow(max(dot(vd, reflectDir), 0.0), 3);
}
