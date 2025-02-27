#version 320 es
precision mediump float;
#define PI 3.14159265358979323846f;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


vec2 rotate2D (vec2 _st, float _angle) {
    _st -= 0.5;
    _st =  mat2(cos(_angle), -sin(_angle),
    sin(_angle), cos(_angle)) * _st;
    _st += 0.5;
    return _st;
}

vec2 tile (vec2 _st, float _zoom) {
    _st *= _zoom;
    return fract(_st);
}

vec2 rotateTilePattern(vec2 _st){

    //  Scale the coordinate system by 2x2
    _st *= 2.0;

    //  Give each cell an index number
    //  according to its position
    float index = 0.0;
    index += step(1., mod(_st.x, 2.0));
    index += step(1., mod(_st.y, 2.0))*2.0;

    //      |
    //  2   |   3
    //      |
    //--------------
    //      |
    //  0   |   1
    //      |

    // Make each cell between 0.0 - 1.0
    _st = fract(_st);

    // Rotate each cell according to the index
    if (index == 1.0){
        //  Rotate cell 1 by 90 degrees
        float angle = 0.5* PI;
        _st = rotate2D(_st, angle);
    } else if (index == 2.0){
        //  Rotate cell 2 by -90 degrees
        float angle =  - 0.5 * PI;
        _st = rotate2D(_st, angle);
    } else if (index == 3.0){
        //  Rotate cell 3 by 180 degrees
        float angle = PI;
        _st = rotate2D(_st, angle);
    }

    return _st;
}


void main() {
    vec2 st = gl_FragCoord.xy / u_resolution;
    st.x *= u_resolution.x / u_resolution.y;
    vec3 color = vec3(0.0);

    st = tile(st, 3.0);
    st = rotateTilePattern(st);

    // Make more interesting combinations
    //        st = tile(st, 2.0);
    float angle2D1 = - u_time *0.25 *PI;
    st = rotate2D(st, angle2D1);
    st = rotateTilePattern(st*2.0);
    float angle2D2 = u_time*0.25 * PI;
    st = rotate2D(st, angle2D2);

    // step(st.x,st.y) just makes a b&w triangles
    // but you can use whatever design you want.
    // Uncomment to see the space coordinates
    color = vec3(step(st.x, st.y));

    FragColor = vec4(color, 1.0f);
}