#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

//uniform vec4 clipplane;

void main()
{
    TexCoords = aTexCoords;
    //Normal = mat3(transpose(inverse(modelMatrix))) * aNormal;  
    Normal=aNormal;
    FragPos=vec3(modelMatrix * vec4(aPos, 1.0));
    //vec4 worldPosition = u_model * vec4(aPos,1.0);
    //gl_ClipDistance[0] = dot(worldPosition, clipplane);
    
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);
    //gl_ClipDistance[0] = 1;
}