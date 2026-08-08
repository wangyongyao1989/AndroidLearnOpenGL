#version 320 es
precision mediump float;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform vec2 u_mouse;
uniform float u_time;//传入的时间变量



void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    st.x *= u_resolution.x/u_resolution.y;
    vec3 color = vec3(0.0);
    // Cell positions
    vec2 point[5];
    point[0] = vec2(0.83, 0.75);
    point[1] = vec2(0.60, 0.07);
    point[2] = vec2(0.28, 0.64);
    point[3] =  vec2(0.31, 0.26);
    point[4] = u_mouse/u_resolution;

    float m_dist = 1.;// minimum distance

    // Iterate through the points positions
    for (int i = 0; i < 5; i++) {
        float dist = distance(st, point[i]);

        // Keep the closer distance
        m_dist = min(m_dist, dist);
    }

    // Draw the min distance (distance field)
    color += m_dist;

    // Show isolines
    // color -= step(.7,abs(sin(50.0*m_dist)))*.3;


    FragColor = vec4(color, 1.0f);
}