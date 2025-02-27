#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


mat2 scale(vec2 _scale){
    return mat2(_scale.x, 0.0,
    0.0, _scale.y);
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

float crossS(in vec2 _st, float _size){
    return box(_st, vec2(_size, _size/4.0)) +
    box(_st, vec2(_size/4.0, _size));
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 color = vec3(0.0);

    st -= vec2(0.5);
    st = scale(vec2(sin(u_time)+1.0)) * st;
    st += vec2(0.5);

    // 在背景上显示空间的坐标
    color = vec3(st.x, st.y, 0.0);

    // 在视窗上添加形状
    color += vec3(crossS(st, 0.2));

    FragColor = vec4(color, 1.0f);
}