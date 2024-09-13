#version 320 es
precision mediump float;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

//光照位置
uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    //环境光照
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //向量进行标准化
    vec3 norm = normalize(Normal);
    //光照方向 光的方向向量是光源位置向量与片段位置向量之间的向量差
    vec3 lightDir = normalize(lightPos - FragPos);
    //对norm和lightDir向量进行点乘，计算光源对当前片段实际的漫反射影响。
    //结果值再乘以光的颜色，得到漫反射分量。两个向量之间的角度越大，漫反射分量就会越小
    //如果两个向量之间的角度大于90度，点乘的结果就会变成负数，这样会导致漫反射分量变为负数。
    //为此，我们使用max函数返回两个参数之间较大的参数
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    //环境光分量和漫反射分量相加，之后乘以物体的颜色，
    vec3 result = (ambient + diffuse) * objectColor;
    //最后来获取片段的输出颜色
    FragColor = vec4(result, 1.0);
}