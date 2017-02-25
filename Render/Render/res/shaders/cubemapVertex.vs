#version 330 core
precision highp float;

layout (location = 0) in vec3 position;
out vec3 texCoords;

uniform mat4 transform;

void main()
{
    gl_Position = transform * vec4(position, 1.0);  
    texCoords = vec3(position.x, position.y, position.z);
} 