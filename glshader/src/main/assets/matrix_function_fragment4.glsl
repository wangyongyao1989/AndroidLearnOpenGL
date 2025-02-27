#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


// YUV to RGB matrix
mat3 yuv2rgb = mat3(1.0, 0.0, 1.13983,
1.0, -0.39465, -0.58060,
1.0, 2.03211, 0.0);

// RGB to YUV matrix
mat3 rgb2yuv = mat3(0.2126, 0.7152, 0.0722,
-0.09991, -0.33609, 0.43600,
0.615, -0.5586, -0.05639);



void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 color = vec3(0.0);

    // UV值从-1到1
    // 因此，我们需要重新映射st（0.0到1.0）
    st -= 0.5;// becomes -0.5 to 0.5
    st *= 2.0;// becomes -1.0 to 1.0

    // 我们将st作为三维向量的y&z值传递给正确乘以3x3矩阵
    color = yuv2rgb * vec3(0.5, st.x, st.y);

    FragColor = vec4(color, 1.0f);
}