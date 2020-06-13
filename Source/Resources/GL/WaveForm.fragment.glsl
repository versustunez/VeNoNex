#version 330 core
in vec4 newColor;

out vec4 fragColor;
void main()
{
    fragColor = newColor;
}