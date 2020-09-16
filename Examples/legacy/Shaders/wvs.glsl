#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

out vec3 ourColor;
uniform mat4 gWorld;

void main()
{
    gl_Position = gWorld * vec4(position, 1.0f);
    ourColor = color;
}