#version 320 es
precision mediump float;
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{
        //灰度加权
       FragColor = texture(screenTexture, TexCoords);
       float average = 0.2126 * FragColor.r + 0.7152 * FragColor.g + 0.0722 * FragColor.b;
       FragColor = vec4(average, average, average, 1.0);
}