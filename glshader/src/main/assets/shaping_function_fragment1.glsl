#version 320 es
precision mediump float;

out vec4 FragColor;

uniform vec2 u_resolution;
uniform float u_time;

// Plot a line on Y using a value between 0.0-1.0
float plot(vec2 st) {
    return smoothstep(0.02f, 0.0f, abs(st.y - st.x));
}

void main() {
	vec2 st = gl_FragCoord.xy / u_resolution;

    float y = st.x;

    vec3 color = vec3(st.x,st.x,abs(sin(u_time)));

    // Plot a line
    float pct = plot(st);

    color = (1.0f - pct) * color + pct * vec3(1.0f,0.0f,0.0f);

	FragColor = vec4(color , 1.0f);
}