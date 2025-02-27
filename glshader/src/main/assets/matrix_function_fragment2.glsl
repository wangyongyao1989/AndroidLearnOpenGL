#version 320 es
precision mediump float;
#define PI 3.14159265359;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


mat2 rotate2d(float _angle){
    return mat2(cos(_angle), -sin(_angle),
    sin(_angle), cos(_angle));
}

float box(in vec2 _st, in vec2 _size){
    _size = vec2(0.5) - _size*0.5;
    vec2 uv = smoothstep(_size,
    _size+vec2(0.001),
    _st);
    uv *= smoothstep(_size,
    _size+vec2(0.001),
    vec2(1.0)-_st);
    return uv.x*uv.y;
}

float crossR(in vec2 _st, float _size){
    return box(_st, vec2(_size, _size/4.)) +
    box(_st, vec2(_size/4., _size));
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 color = vec3(0.0);

    // 将空间从中心移动到vec2（0.0）
    st -= vec2(0.5);
    // 旋转空间
    float angle = sin(u_time)*PI;
    st = rotate2d(angle) * st;
    // 将其移回原位
    st += vec2(0.5);

    // 在背景上显示空间的坐标
     color = vec3(st.x,st.y,0.0);

    // 在视窗上添加形状
    color += vec3(crossR(st, 0.4));

    FragColor = vec4(color, 1.0f);
}