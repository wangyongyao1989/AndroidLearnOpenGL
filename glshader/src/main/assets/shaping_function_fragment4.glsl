#version 320 es
precision mediump float;

#define PI 3.14159265359;

out vec4 FragColor;

uniform vec2 u_resolution;

float plot(vec2 st, float pct){
  return  smoothstep( pct-0.02f, pct, st.y) -
          smoothstep( pct, pct+0.02f, st.y);
}

void main() {
	vec2 st = gl_FragCoord.xy / u_resolution;
    float y;
    float x = st.x;

//    y = mod(x,0.5); // 返回 x 对 0.5 取模的值
//     y = fract(x); // 仅仅返回数的小数部分
     y = ceil(x);  // 向正无穷取整
    // y = floor(x); // 向负无穷取整
    // y = sign(x);  // 提取 x 的正负号
    // y = abs(x);   // 返回 x 的绝对值
    // y = clamp(x,0.0,1.0); // 把 x 的值限制在 0.0 到 1.0
    // y = min(0.0,x);   // 返回 x 和 0.0 中的较小值
    // y = max(0.0,x);   // 返回 x 和 0.0 中的较大值

    // Plot a line
    float pct = plot(st,y);

    vec3 color = pct * vec3(1.0f,0.0f,0.0f);

	FragColor = vec4(color , 1.0f);
}