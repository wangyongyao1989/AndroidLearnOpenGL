#version 320 es
precision mediump float;

#define PI 3.14159265359;

out vec4 FragColor;

uniform vec2 u_resolution;

//  Function from Iñigo Quiles
//  www.iquilezles.org/www/articles/functions/functions.htm
float pcurve(float x, float a, float b){
    float k = pow(a+b, a+b) / (pow(a, a)*pow(b, b));
    return k * pow(x, a) * pow(1.0-x, b);
}


float plot(vec2 st, float pct){
    return smoothstep(pct-0.02, pct, st.y) -
    smoothstep(pct, pct+0.02, st.y);
}

void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    float y;
    float x = st.x;

    y  = pcurve(st.x, 3.0, 1.0);
    // Plot a line
    float pct = plot(st, y);

    vec3 color = pct * vec3(1.0f, 0.0f, 0.0f);

    FragColor = vec4(color, 1.0f);
}