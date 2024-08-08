#version 320 es
precision mediump float;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //光照和物体颜色的分量
    FragColor = vec4(lightColor * objectColor, 1.0);
}