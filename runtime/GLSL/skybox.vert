#version 430 core
layout (location = 0) in vec3 aPos;

out vec3 TexCoords;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;

//uniform vec4 clipplane;

void main()
{
    TexCoords = aPos;
    vec4 pos = projectionMatrix * viewMatrix * vec4(aPos, 1.0);
    /*vec4 worldPosition = vec4(aPos,1.0);
    gl_ClipDistance[0] = dot(worldPosition, clipplane);*/
    gl_Position = pos.xyww;
}  