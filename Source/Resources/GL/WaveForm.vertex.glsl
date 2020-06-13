#version 330 core
in vec4 position;
uniform vec4 color = vec4(1f, 1f, 1f, 1f);

out vec4 newColor;
void main()
{
    gl_Position = position;
    newColor = color;
}