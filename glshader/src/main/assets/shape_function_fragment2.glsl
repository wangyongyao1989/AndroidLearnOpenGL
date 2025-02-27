#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;
    //获取屏幕分辨率的长宽比
    float rateXY = u_resolution.x / u_resolution.y;

    float pct = 0.0;

    vec2 st1 = vec2(st.x, st.y / rateXY);
    // 1. 像素到中心的距离
    pct = distance(st1, vec2(0.5, 0.5 / rateXY));

    // 2. 从像素到中心的矢量长度
    // vec2 toCenter = vec2(0.5, 0.5)-st1;
    // pct = length(toCenter);

    // 3. 从像素到中心的向量的平方根
    // vec2 tC = vec2(0.5, 0.5)-st1;
    // pct = sqrt(tC.x*tC.x+tC.y*tC.y);

    vec3 color = vec3(pct);

    FragColor = vec4(color, 1.0f);
}