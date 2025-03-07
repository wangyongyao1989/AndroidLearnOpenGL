#version 320 es
precision mediump float;

#define PI 3.141592653589793f;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


vec3 colorA = vec3(0.149, 0.141, 0.912);
vec3 colorB = vec3(1.000, 0.833, 0.224);

float plot (vec2 st, float pct){
    return smoothstep(pct-0.01, pct, st.y) -
    smoothstep(pct, pct+0.01, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    vec3 color = vec3(0.0);

    vec3 pct = vec3(st.x);

    pct.r = smoothstep(0.0, 1.0, st.x);
    float result = st.x * PI;
    pct.g = sin(result);
    pct.b = pow(st.x, 0.5);

    color = mix(colorA, colorB, pct);

    // Plot transition lines for each channel
    color = mix(color, vec3(1.0, 0.0, 0.0), plot(st, pct.r));
    color = mix(color, vec3(0.0, 1.0, 0.0), plot(st, pct.g));
    color = mix(color, vec3(0.0, 0.0, 1.0), plot(st, pct.b));

    FragColor = vec4(color, 1.0f);
}