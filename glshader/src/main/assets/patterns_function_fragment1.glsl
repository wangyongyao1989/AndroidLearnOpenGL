#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


float circle(in vec2 _st, in float _radius){
    vec2 l = _st-vec2(0.5);
    return 1.0-smoothstep(_radius-(_radius*0.01),
    _radius+(_radius*0.01),
    dot(l, l)*4.0);
}
void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    st.x *= u_resolution.x / u_resolution.y;

    vec3 color = vec3(0.0);

    st *= 5.0;// Scale up the space by 3
    st = fract(st);// Wrap around 1.0

    // Now we have 9 spaces that go from 0-1

    color = vec3(st, 0.0);
    //    color = vec3(circle(st, 0.5));

    FragColor = vec4(color, 1.0f);
}