#version 320 es
precision mediump float;

out vec4 FragColor;         //out代表输出至下一个着色器

uniform vec2 u_resolution;  //视窗的分辨率
uniform float u_time;       //传入的时间变量

float plot(vec2 st, float pct){
    return  smoothstep( pct-0.02, pct, st.y) -
    smoothstep( pct, pct+0.02, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy/u_resolution;

    //插值函数需要输入两个参数。第一个是极限或阈值，
    //第二个是我们想要检测或通过的值。对任何小于阈值的值，返回0.0，大于阈值，则返回1.0。
    float y = step(0.5,st.x);

    vec3 color = vec3(y);

    float pct = plot(st,y);
    color = (1.0-pct)*color+pct*vec3(1.0,0.0,0.0);

    FragColor = vec4(color , 1.0f);
}
