#version 410 core

in  vec2 fTexCoord;
out vec4 FragColor;

uniform float uStrength;
uniform sampler2D uTexture;

const vec3 lumWeights = vec3(0.2125, 0.7154, 0.0721);

void main() {
    vec3 texColor = texture(uTexture, fTexCoord).rgb;
    float luminance = dot(texColor, lumWeights);
    vec3 greyScaleColor = vec3(luminance);

    FragColor = vec4(mix(texColor, greyScaleColor, uStrength), 1.0);
}