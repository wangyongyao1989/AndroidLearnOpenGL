#version 320 es

layout (location = 0) in vec3 aPos;     // 位置变量的属性位置值为0
layout (location = 1) in vec3 aTexCoord;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // 注意乘法要从右向左读
    gl_Position = projection * view * model * vec4(aPos, 1.0f);
   	TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}