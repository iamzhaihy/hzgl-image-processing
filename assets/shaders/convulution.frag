#version 410 core

in  vec2 fTexCoord;
out vec4 FragColor;

uniform float uKernel[9];
uniform float uKernelWeight;

uniform vec2 uTextureSize;
uniform sampler2D uTexture;

void main() {
    vec2 onePixel = vec2(1.0, 1.0) / uTextureSize;

    vec4 colorSum = texture(uTexture, fTexCoord + onePixel * vec2(-1, 1)) * uKernel[0] 
        + texture(uTexture, fTexCoord + onePixel * vec2( 0,  1)) * uKernel[1] 
        + texture(uTexture, fTexCoord + onePixel * vec2( 1,  1)) * uKernel[2] 
        + texture(uTexture, fTexCoord + onePixel * vec2(-1,  0)) * uKernel[3] 
        + texture(uTexture, fTexCoord + onePixel * vec2( 0,  0)) * uKernel[4] 
        + texture(uTexture, fTexCoord + onePixel * vec2( 1,  0)) * uKernel[5] 
        + texture(uTexture, fTexCoord + onePixel * vec2(-1, -1)) * uKernel[6] 
        + texture(uTexture, fTexCoord + onePixel * vec2( 0, -1)) * uKernel[7] 
        + texture(uTexture, fTexCoord + onePixel * vec2( 1, -1)) * uKernel[8];

    FragColor = vec4((colorSum/uKernelWeight).rgb, 1);
}