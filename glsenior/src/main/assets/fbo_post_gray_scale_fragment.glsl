#version 320 es
precision mediump float;
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTexture;

void main()
{       //灰度
       FragColor = texture(screenTexture, TexCoords);
       float average = (FragColor.r + FragColor.g + FragColor.b) / 3.0;
       FragColor = vec4(average, average, average, 1.0);
}