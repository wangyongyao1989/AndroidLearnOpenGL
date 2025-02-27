#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;

    st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(0.0);
    float d = 0.0;

    // Remap the space to -1. to 1.
    st = st *2.0-1.0;

    // Make the distance field
    d = length(abs(st)-0.3);
    // d = length( min(abs(st)-.3,0.) );
    // d = length( max(abs(st)-.3,0.) );

    // Visualize the distance field
    color = vec3(fract(d*10.0));

    // Drawing with the distance field
    //    color = vec3(step(0.3, d));
    //    color = vec3(step(0.3,d) * step(d,0.4));

    FragColor = vec4(color, 1.0f);
}