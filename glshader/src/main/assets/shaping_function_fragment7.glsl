#version 320 es
precision mediump float;

#define PI 3.14159265359;

out vec4 FragColor;

uniform vec2 u_resolution;

float doubleCircleSigmoid (float x, float a){
    float min_param_a = 0.0;
    float max_param_a = 1.0;
    a = max(min_param_a, min(max_param_a, a));

    float y = 0.0;
    if (x<=a){
        y = a - sqrt(a*a - x*x);
    } else {
        y = a + sqrt(pow((1.0-a), 2.0) - pow((x-1.0), 2.0));
    }
    return y;
}

float plot(vec2 st, float pct){
    return smoothstep(pct-0.02f, pct, st.y) -
    smoothstep(pct, pct+0.02f, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    float y;
    float x = st.x;

    y = doubleCircleSigmoid(st.x, 0.3);
    // Plot a line
    float pct = plot(st, y);

    vec3 color = pct * vec3(1.0f, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
}