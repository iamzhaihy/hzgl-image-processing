#version 410 core

in  vec2 fTexCoord;
out vec4 FragColor;

uniform vec2 uTextureSize;
uniform sampler2D uTexture;

void main()
{
    FragColor = vec4(texture(uTexture, fTexCoord).rgb, 1.0);
}