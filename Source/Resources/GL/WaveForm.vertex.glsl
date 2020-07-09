#version 330 core
in vec4 position;
uniform vec4 color = vec4(1f, 1f, 1f, 1f);
uniform vec4 gradientColor = vec4(1f, 1f, 1f, 1f);

out vec4 newColor;
out vec4 newGradientColor;
out vec4 sPosition;
void main()
{
    gl_Position = position;
    newColor = color;
    newGradientColor = gradientColor;
    sPosition = position;
}