#version 330 core
in vec4 newColor;
in vec4 newGradientColor;
in vec4 sPosition;

out vec4 fragColor;
void main()
{
    if (newColor == newGradientColor) {
        fragColor = newColor;
    } else {
        vec2 st = sPosition.xy;
        float mixValue = distance(st, vec2(0, 0));
        vec3 color = mix(newGradientColor.xyz, newColor.xyz, mixValue);
        fragColor = vec4(color, mixValue);
    }

}