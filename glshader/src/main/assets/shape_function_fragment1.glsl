#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    vec3 color = vec3(0.0);

    // bottom-left
    vec2 bl = step(vec2(0.1), st);
    float pct = bl.x * bl.y;

    // top-right
    vec2 tr = step(vec2(0.1), 1.0-st);
    pct *= tr.x * tr.y;

    color = vec3(pct);

    FragColor = vec4(color, 1.0f);
}