#version 320 es
precision mediump float;

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

//光照位置
uniform vec3 lightPos;
//观察者位置
uniform vec3 viewPos;
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

    //镜面强度(Specular Intensity)变量，给镜面高光一个中等亮度颜色，让它不要产生过度的影响
    float specularStrength = 0.5;
    //计算视线方向向量，和对应的沿着法线轴的反射向量
    vec3 viewDir = normalize(viewPos - FragPos);
    //对lightDir向量进行了取反。reflect函数要求第一个向量是从光源指向片段位置的向量，但是lightDir当前正好相反，
    //是从片段指向光源（由先前我们计算lightDir向量时，减法的顺序决定）。
    vec3 reflectDir = reflect(-lightDir, norm);
    //计算镜面分量
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 specular = specularStrength * spec * lightColor;

    //加到环境光分量和漫反射分量里，再用结果乘以物体的颜色
    vec3 result = (ambient + diffuse + specular) * objectColor;
    //最后来获取片段的输出颜色
    FragColor = vec4(result, 1.0);
}