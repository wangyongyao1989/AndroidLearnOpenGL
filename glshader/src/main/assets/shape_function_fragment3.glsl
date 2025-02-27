#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量

float circle(in vec2 _st, in float _radius){
    vec2 dist = _st-vec2(0.5, 0.3);
    return 1.-smoothstep(_radius-(_radius*0.01),
    _radius+(_radius*0.01),
    dot(dist, dist)*5.0);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;
    //获取屏幕分辨率的长宽比
    float rateXY = u_resolution.x / u_resolution.y;

    vec2 st1 = vec2(st.x * rateXY, st.y);

    vec3 color = vec3(circle(st1, 0.2));

    FragColor = vec4(color, 1.0f);
}