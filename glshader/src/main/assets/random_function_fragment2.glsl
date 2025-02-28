#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


float random (vec2 st) {
    return fract(sin(dot(st.xy,
    vec2(12.9898, 78.233)))*43758.5453123);
}


void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;

    st *= 10.0;// Scale the coordinate system by 10
    vec2 ipos = floor(st);// get the integer coords
    vec2 fpos = fract(st);// get the fractional coords

    // Assign a random value based on the integer coord
    vec3 color = vec3(random(ipos));

    FragColor = vec4(color, 1.0f);
}