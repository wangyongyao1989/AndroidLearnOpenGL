#version 320 es
precision mediump float;

out vec4 FragColor;         //out代表输出至下一个着色器

uniform vec2 u_resolution;  //视窗的分辨率
uniform float u_time;       //传入的时间变量
uniform float uu;

// Plot a line on Y using a value between 0.0-1.0
float plot(vec2 st) {
    //返回一个float类型的值，这个值的范围在[0, 1]之间，
    //代表了输入值经过平滑插值后的结果。
    return smoothstep(0.02f, 0.0f, abs(st.y - st.x));
}

void main() {
    //1.传入每个像素的xy除视窗的分辨率
    vec2 st = gl_FragCoord.xy / u_resolution;
    //2.获取st的x分量，加载uniform中的u_time，
    //得到跟随时间的变换的渐变色
    vec3 color = vec3(st.x,st.x,abs(sin(u_time)));
    // Plot a line
    float pct = plot(st);
    //3.【(1.0f - pct) * color】表示除直线外的渐变颜色，
    //【pct * vec3(1.0f,0.0f,0.0f)】表示附着直线的颜色。
    color = (1.0f - pct) * color + pct * vec3(1.0f,0.0f,0.0f);
    FragColor = vec4(color , 1.0f);
}