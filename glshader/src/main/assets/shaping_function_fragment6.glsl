#version 320 es
precision mediump float;

#define PI 3.14159265359;

out vec4 FragColor;

uniform vec2 u_resolution;

float exponentialEasing (float x, float a){

    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    a = max(min_param_a, min(max_param_a, a));

    if (a < 0.5){
        // emphasis
        a = 2.0*(a);
        float y = pow(x, a);
        return y;
    } else {
        // de-emphasis
        a = 2.0*(a-0.5);
        float y = pow(x, 1.0/(1.0-a));
        return y;
    }
}

float plot(vec2 st, float pct){
    return smoothstep(pct-0.02f, pct, st.y) -
    smoothstep(pct, pct+0.02f, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    float y;
    float x = st.x;

    y = exponentialEasing(st.x, 0.3);
    // Plot a line
    float pct = plot(st, y);

    vec3 color = pct * vec3(1.0f, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
}