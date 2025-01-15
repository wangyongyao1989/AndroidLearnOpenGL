#version 320 es
precision mediump float;
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

void main()
{
     vec4 texColor = texture(texture1, TexCoords);
     //discard命令，一旦被调用，它就会保证片段不会被进一步处理，所以就不会进入颜色缓冲。
     if(texColor.a < 0.1)
        discard;
     FragColor = texture(texture1, TexCoords);
}