#version 320 es
precision mediump float;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //把环境光照添加到场景里非常简单。我们用光的颜色乘以一个很小的常量环境因子，再乘以物体的颜色，
    //然后将最终结果作为片段的颜色.
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);
    //光照和物体颜色的分量
   // FragColor = vec4(lightColor * objectColor, 1.0);
}