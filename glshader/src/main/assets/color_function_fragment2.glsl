#version 320 es
precision mediump float;

#define PI 3.141592653589793f;
#define HALF_PI 1.5707963267948966f;

out vec4 FragColor;//out代表输出至下一个着色器

uniform vec2 u_resolution;//视窗的分辨率
uniform float u_time;//传入的时间变量


// Robert Penner's easing functions in GLSL
// https://github.com/stackgl/glsl-easings
float linear(float t) {
    return t;
}

float exponentialIn(float t) {
    return t == 0.0 ? t : pow(2.0, 10.0 * (t - 1.0));
}

float exponentialOut(float t) {
    return t == 1.0 ? t : 1.0 - pow(2.0, -10.0 * t);
}

float exponentialInOut(float t) {
    return t == 0.0 || t == 1.0
    ? t
    : t < 0.5
    ? +0.5 * pow(2.0, (20.0 * t) - 10.0)
    : -0.5 * pow(2.0, 10.0 - (t * 20.0)) + 1.0;
}

float sineIn(float t) {
    float result = (t - 1.0) * HALF_PI;
    return sin(result) + 1.0f;
}

float sineOut(float t) {
    float result = t * HALF_PI;
    return sin(result);
}

float qinticIn(float t) {
    return pow(t, 5.0);
}

float qinticOut(float t) {
    return 1.0 - (pow(t - 1.0, 5.0));
}

float qinticInOut(float t) {
    return t < 0.5
    ? +16.0 * pow(t, 5.0)
    : -0.5 * pow(2.0 * t - 2.0, 5.0) + 1.0;
}

float quarticIn(float t) {
    return pow(t, 4.0);
}

float quarticOut(float t) {
    return pow(t - 1.0, 3.0) * (1.0 - t) + 1.0;
}

float quarticInOut(float t) {
    return t < 0.5
    ? +8.0 * pow(t, 4.0)
    : -8.0 * pow(t - 1.0, 4.0) + 1.0;
}

float quadraticInOut(float t) {
    float p = 2.0 * t * t;
    return t < 0.5 ? p : -p + (4.0 * t) - 1.0;
}

float quadraticIn(float t) {
    return t * t;
}

float quadraticOut(float t) {
    return -t * (t - 2.0);
}

float cubicIn(float t) {
    return t * t * t;
}

float cubicOut(float t) {
    float f = t - 1.0;
    return f * f * f + 1.0;
}

float cubicInOut(float t) {
    return t < 0.5
    ? 4.0 * t * t * t
    : 0.5 * pow(2.0 * t - 2.0, 3.0) + 1.0;
}

float elasticIn(float t) {
    float result = 13.0 * t * HALF_PI;

    return sin(result) * pow(2.0, 10.0 * (t - 1.0));
}

float elasticOut(float t) {
    float result = -13.0 * (t + 1.0) * HALF_PI;
    return sin(result) * pow(2.0, -10.0 * t) + 1.0;
}

float elasticInOut(float t) {
    float result1 = 13.0 * HALF_PI;

    float result2 = -13.0 * HALF_PI;
    return t < 0.5
    ? 0.5 * sin(result1 * 2.0 * t) * pow(2.0, 10.0 * (2.0 * t - 1.0))
    : 0.5 * sin(result2 * ((2.0 * t - 1.0) + 1.0)) * pow(2.0, -10.0 * (2.0 * t - 1.0)) + 1.0;
}

float circularIn(float t) {
    return 1.0 - sqrt(1.0 - t * t);
}

float circularOut(float t) {
    return sqrt((2.0 - t) * t);
}

float circularInOut(float t) {
    return t < 0.5
    ? 0.5 * (1.0 - sqrt(1.0 - 4.0 * t * t))
    : 0.5 * (sqrt((3.0 - 2.0 * t) * (2.0 * t - 1.0)) + 1.0);
}

float bounceOut(float t) {
    const float a = 4.0 / 11.0;
    const float b = 8.0 / 11.0;
    const float c = 9.0 / 10.0;

    const float ca = 4356.0 / 361.0;
    const float cb = 35442.0 / 1805.0;
    const float cc = 16061.0 / 1805.0;

    float t2 = t * t;

    return t < a
    ? 7.5625 * t2
    : t < b
    ? 9.075 * t2 - 9.9 * t + 3.4
    : t < c
    ? ca * t2 - cb * t + cc
    : 10.8 * t * t - 20.52 * t + 10.72;
}

float bounceIn(float t) {
    return 1.0 - bounceOut(1.0 - t);
}

float bounceInOut(float t) {
    return t < 0.5
    ? 0.5 * (1.0 - bounceOut(1.0 - t * 2.0))
    : 0.5 * bounceOut(t * 2.0 - 1.0) + 0.5;
}

float backIn(float t) {
    float result = t * PI;
    return pow(t, 3.0) - t * sin(result);
}

float backOut(float t) {
    float f = 1.0 - t;
    float result = f * PI;
    return 1.0 - (pow(f, 3.0) - f * sin(result));
}

float backInOut(float t) {
    float f = t < 0.5 ? 2.0 * t : 1.0 - (2.0 * t - 1.0);
    float result = f * PI;
    float g = pow(f, 3.0) - f * sin(result);

    return t < 0.5
    ? 0.5 * g
    : 0.5 * (1.0 - g) + 0.5;
}

void main() {
    vec3 colorA = vec3(0.149, 0.141, 0.912);
    vec3 colorB = vec3(1.000, 0.833, 0.224);

    float t = u_time * 0.5;
    float pct;
//    pct = cubicInOut(abs(fract(t)*2.0-1.0));
    pct = exponentialIn(t);
    vec3 color = mix(colorA, colorB, pct);
    FragColor = vec4(color, 1.0f);
}