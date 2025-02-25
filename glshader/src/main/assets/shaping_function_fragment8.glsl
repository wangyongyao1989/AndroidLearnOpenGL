#version 320 es
precision mediump float;

#define PI 3.14159265359;

out vec4 FragColor;

uniform vec2 u_resolution;

float quadraticBezier (float x, float a, float b){
    // adapted from BEZMATH.PS (1993)
    // by Don Lancaster, SYNERGETICS Inc.
    // http://www.tinaja.com/text/bezmath.html

    float epsilon = 0.00001;
    a = max(0.0, min(1.0, a));
    b = max(0.0, min(1.0, b));
    if (a == 0.5){
        a += epsilon;
    }

    // solve t from x (an inverse operation)
    float om2a = 1.0 - 2.0*a;
    float t = (sqrt(a*a + om2a*x) - a)/om2a;
    float y = (1.0-2.0*b)*(t*t) + (2.0*b)*t;
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

    y = quadraticBezier(st.x, 0.001, 5.0);
    // Plot a line
    float pct = plot(st, y);

    vec3 color = pct * vec3(1.0f, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
}