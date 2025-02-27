#version 320 es
precision mediump float;

#define PI 3.14159265359;

out vec4 FragColor;

uniform vec2 u_resolution;

float blinnWyvillCosineApproximation (float x){
    float x2 = x*x;
    float x4 = x2*x2;
    float x6 = x4*x2;

    float fa = (4.0/9.0);
    float fb = (17.0/9.0);
    float fc = (22.0/9.0);

    float y = fa*x6 - fb*x4 + fc*x2;
    return y;
}

float doubleCubicSeat (float x, float a, float b){

    float epsilon = 0.00001;
    float min_param_a = 0.0 + epsilon;
    float max_param_a = 1.0 - epsilon;
    float min_param_b = 0.0;
    float max_param_b = 1.0;
    a = min(max_param_a, max(min_param_a, a));
    b = min(max_param_b, max(min_param_b, b));

    float y = 0.00000f;
    if (x <= a){
        y = b - (b * pow(1.0-x/a, 3.0));
    } else {
        y = b + (1.0-b)*pow((x-a)/(1.0-a), 3.0);
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

    y = blinnWyvillCosineApproximation(x);
    //    y = doubleCubicSeat(x, 5.0f, 5.0f);
    // Plot a line
    float pct = plot(st, y);

    vec3 color = pct * vec3(1.0f, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
}