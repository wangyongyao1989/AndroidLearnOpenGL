#version 320 es
precision mediump float;
#define PI 3.1415926535897932384626433832795;
out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform vec2 u_mouse;
uniform float u_time;//传入的时间变量


//this is a basic Pseudo Random Number Generator
float hash(in float n)
{
    return fract(sin(n)*43758.5453123);
}

vec2 random2(vec2 p) {
    return fract(sin(vec2(dot(p, vec2(127.1, 311.7)), dot(p, vec2(269.5, 183.3))))*43758.5453);
}

vec3 voronoi(in vec2 x) {
    vec2 n = floor(x);
    vec2 f = fract(x);

    // first pass: regular voronoi
    vec2 mg, mr;
    float md = 8.0;
    for (int j= -1; j <= 1; j++) {
        for (int i= -1; i <= 1; i++) {
            vec2 g = vec2(float(i), float(j));
            vec2 o = random2(n + g);
            o = 0.5 + 0.5*sin(u_time + 6.2831*o);

            vec2 r = g + o - f;
            float d = dot(r, r);

            if (d<md) {
                md = d;
                mr = r;
                mg = g;
            }
        }
    }

    // second pass: distance to borders
    md = 8.0;
    for (int j= -2; j <= 2; j++) {
        for (int i= -2; i <= 2; i++) {
            vec2 g = mg + vec2(float(i), float(j));
            vec2 o = random2(n + g);
            o = 0.5 + 0.5*sin(u_time + 6.2831*o);

            vec2 r = g + o - f;

            if (dot(mr-r, mr-r)>0.00001) {
                md = min(md, dot(0.5*(mr+r), normalize(r-mr)));
            }
        }
    }
    return vec3(md, mr);
}
void main() {
    //"squarified" coordinates
    vec2 xy = (2.* gl_FragCoord.xy - u_resolution.xy) / u_resolution.y;

    //rotating light
    vec3 center = vec3(sin(u_time), 1., cos(u_time * .5));

    //temporary vector
    vec3 pp = vec3(0.);

    //maximum distance of the surface to the center (try a value of 0.1 for example)
    float length = 4.;

    //this is the number of cells
    const float count = 100.;

    for (float i = 0.; i < count; i+=1.)
    {
        //random cell: create a point around the center

        //gets a 'random' angle around the center
        float t1 =   u_time *PI ;
        float hashPi = hash(i) * PI;
        float an = sin(t1 * .00001) - hashPi * 2.;

        //gets a 'random' radius ( the 'spacing' between cells )
        float ra = sqrt(hash(an)) * .5;

        //creates a temporary 2d vector
        vec2 p = vec2(center.x + cos(an) * ra, center.z + sin(an) * ra);

        //finds the closest cell from the fragment's XY coords

        //compute the distance from this cell to the fragment's coordinates
        float di = distance(xy, p);

        //and check if this length is inferior to the minimum length
        length = min(length, di);

        //if this cell was the closest
        if (length == di)
        {
            //stores the XY values of the cell and compute a 'Z' according to them
            pp.xy = p;
            pp.z = i / count * xy.x * xy.y;
        }
    }

    //shimmy shake:
    //uses the temp vector's coordinates and uses the angle and the temp vector
    //to create light & shadow (quick & dirty )
    vec3 shade = vec3(1.) * (1. - max(0.0, dot(pp, center)));

    FragColor = vec4(pp + shade, 1.0f);
}