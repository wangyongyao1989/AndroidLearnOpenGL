#version 320 es
precision mediump float;
#define PI 3.14159265358979323846f;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


vec2 rotate2D(vec2 _st, float _angle){
    _st -= 0.5;
    _st =  mat2(cos(_angle), -sin(_angle),
    sin(_angle), cos(_angle)) * _st;
    _st += 0.5;
    return _st;
}

vec2 tile(vec2 _st, float _zoom){
    _st *= _zoom;
    return fract(_st);
}

float box(vec2 _st, vec2 _size, float _smoothEdges){
    _size = vec2(0.5)-_size*0.5;
    vec2 aa = vec2(_smoothEdges*0.5);
    vec2 uv = smoothstep(_size, _size+aa, _st);
    uv *= smoothstep(_size, _size+aa, vec2(1.0)-_st);
    return uv.x*uv.y;
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    st.x *= u_resolution.x / u_resolution.y;
    vec3 color = vec3(0.0);
    // Divide the space in 4
    st = tile(st, 4.0);

    // Use a matrix to rotate the space 45 degrees
    float angle = 0.25f * PI;
    st = rotate2D(st, angle);

    // Draw a square
    color = vec3(box(st, vec2(0.7), 0.01));
//    color = vec3(st, 0.0);

    FragColor = vec4(color, 1.0f);
}