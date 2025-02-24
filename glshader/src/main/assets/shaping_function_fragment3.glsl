#version 320 es
precision mediump float;

#define PI 3.14159265359;

out vec4 FragColor;

uniform vec2 u_resolution;

float plot(vec2 st, float pct){
  return  smoothstep( pct-0.02, pct, st.y) -
          smoothstep( pct, pct+0.02, st.y);
}

void main() {
	vec2 st = gl_FragCoord.xy / u_resolution;

    // Smooth interpolation between 0.1 and 0.9
    float y = smoothstep(0.1,0.9,st.x);

    vec3 color = vec3(y);

    // Plot a line
    float pct = plot(st,y);

    color = (1.0f - pct) * color + pct * vec3(1.0f,0.0f,0.0f);

	FragColor = vec4(color , 1.0f);
}