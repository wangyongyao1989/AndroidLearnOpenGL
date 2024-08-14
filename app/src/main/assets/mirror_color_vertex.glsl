#version 320 es

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    //顶点位置属性乘以模型矩阵（不是观察和投影矩阵）来把它变换到世界空间坐标
    FragPos = vec3(model * vec4(aPos, 1.0));
    //使用inverse和transpose函数自己生成这个法线矩阵，这两个函数对所有类型矩阵都有效
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * vec4(FragPos, 1.0);
}